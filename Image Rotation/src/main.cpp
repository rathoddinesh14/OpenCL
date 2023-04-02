#define __CL_ENABLE_EXCEPTIONS

// opencl version
#define CL_TARGET_OPENCL_VERSION 200

#include <CL/cl.h>
#include "machine.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <stb_image.h>
#include <stb_image_write.h>

using namespace std;

static const int HIST_BINS = 256;

int main() {

    cl_int status;
    Machine machine;
    machine.create_single_context(1, 0);
    machine.create_cmd_queue();

    // create program
    machine.create_build_program("kernels/imagerotation.cl");
    // add kernel
    machine.add_kernel("rotation");
    // get kernel
    cl_kernel kernel = machine.get_kernel("rotation");

    // host data
    float *h_output_img = NULL;
    const float theta = 45.0f;

    // allocate memory and read data from file
    int width = 0, height = 0, nrChannels = 0;
    const char *filename = "assets/cat.bmp";
    unsigned char *img_data = stbi_load(filename, &width, &height, &nrChannels, 0);

    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "nrChannels: " << nrChannels << endl;

    if (img_data == NULL) {
        cout << "Failed to load image " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // create a new image_data with 1 channel
    float *new_img_data = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        // only red
        new_img_data[i] = (float)(img_data[i * nrChannels]);
    }

    free(img_data);

    // image descriptor
    cl_image_desc desc;
    desc.image_type = CL_MEM_OBJECT_IMAGE2D;
    desc.image_width = width;
    desc.image_height = height;
    desc.image_depth = 0;
    desc.image_array_size = 0;
    desc.image_row_pitch = 0;
    desc.image_slice_pitch = 0;
    desc.num_mip_levels = 0;
    desc.num_samples = 0;
    desc.buffer = NULL;

    // image format
    cl_image_format format;
    format.image_channel_order = CL_R;
    format.image_channel_data_type = CL_FLOAT;

    // allocate memory on host
    int image_size = width * height;
    h_output_img = new float[image_size];
    
    // create buffer
    cl_mem input_img = clCreateImage(machine.get_context(),
                    CL_MEM_READ_ONLY, &format, &desc, NULL, &status);

    check_point(status, "Failed to create input image buffer ");

    cl_mem output_img = clCreateImage(machine.get_context(), 
                    CL_MEM_WRITE_ONLY, &format, &desc, NULL, &status);
    
    check_point(status, "Failed to create output image buffer ");

    // write data to device
    size_t origin[3] = {0, 0, 0};
    size_t region[3] = {width, height, 1};
    status = clEnqueueWriteImage(machine.get_cmd_queue(), input_img, CL_TRUE, 
                    origin, region, 0, 0, new_img_data, 0, NULL, NULL);
    
    check_point(status, "Failed to write data to device ");

    // set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input_img);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &output_img);
    status = clSetKernelArg(kernel, 2, sizeof(int), &width);
    status = clSetKernelArg(kernel, 3, sizeof(int), &height);
    status = clSetKernelArg(kernel, 4, sizeof(float), &theta);

    // set work size and index
    size_t indexSpaceSize[2] = {height, width}, workGroupSize[2] = {8, 8};

    // execute kernel
    status = clEnqueueNDRangeKernel(machine.get_cmd_queue(), kernel, 2, NULL, indexSpaceSize, workGroupSize, 0, NULL, NULL);
    check_point(status, "Failed to execute kernel ");

    // wait for kernel to finish
    status = clFinish(machine.get_cmd_queue());
    check_point(status, "Failed to finish kernel ");

    // read data from device
    status = clEnqueueReadImage(machine.get_cmd_queue(), output_img, CL_TRUE, 
                    origin, region, 0, 0, h_output_img, 0, NULL, NULL);

    // print data
    for (int i = 0; i < width * height; i++) {
        cout << h_output_img[i] << " ";
    }
    cout << endl;

    // SAVE IMAGE TO FILE
    stbi_write_bmp("assets/cat_rotated.bmp", width, height, 1, h_output_img);

    // release memory
    clReleaseMemObject(input_img);
    clReleaseMemObject(output_img);

    delete[] h_output_img;
    free(new_img_data);

    return 0;
}