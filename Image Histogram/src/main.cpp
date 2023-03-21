#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include "machine.h"
#include <iostream>
#include <vector>
#include <stb_image.h>

using namespace std;

static const int HIST_BINS = 256;

int main() {

    // host data
    int *hInputImage = NULL;
    int *hOutputHist = NULL;

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

    // considering only one channel
    const int num_elements = width * height;
    const size_t img_size = num_elements * sizeof(int);

    int* h_img_data = new int[num_elements];
    for (int i = 0; i < num_elements; i++) {
        // consider only one channel
        h_img_data[i] = img_data[i * nrChannels];
    }

    // allocate memory on host
    const int hist_size = HIST_BINS * sizeof(int);
    hOutputHist = (int *)malloc(hist_size);
    if (hOutputHist == NULL) {
        cerr << "Failed to allocate host memory." << endl;
        exit(EXIT_FAILURE);
    }

    cl_int status;

    Machine machine;
    machine.create_single_context();
    
    // create buffer
    cl_mem d_a = clCreateBuffer(machine.get_context(), CL_MEM_READ_ONLY, img_size, NULL, &status);
    cl_mem d_b = clCreateBuffer(machine.get_context(), CL_MEM_WRITE_ONLY, hist_size, NULL, &status);

    machine.create_cmd_queue();

    // write data to device
    status = clEnqueueWriteBuffer(machine.get_cmd_queue(), d_a, CL_TRUE, 0, img_size, h_img_data, 0, NULL, NULL);
    int zero = 0;
    status = clEnqueueFillBuffer(machine.get_cmd_queue(), d_b, &zero, sizeof(int), 0, hist_size, 0, NULL, NULL);

    // create program
    machine.create_build_program("kernels/hist.cl");

    // add kernel
    machine.add_kernel("histogram");

    // get kernel
    cl_kernel kernel = machine.get_kernel("histogram");

    // set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    status = clSetKernelArg(kernel, 1, sizeof(int), &num_elements);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_b);

    // set work size and index
    size_t indexSpaceSize[1] = {1024}, workGroupSize[1] = {64};

    // execute kernel
    status = clEnqueueNDRangeKernel(machine.get_cmd_queue(), kernel, 1, NULL, indexSpaceSize, workGroupSize, 0, NULL, NULL);

    // read data from device
    status = clEnqueueReadBuffer(machine.get_cmd_queue(), d_b, CL_TRUE, 0, hist_size, hOutputHist, 0, NULL, NULL);

    // print result
    for (int i = 0; i < HIST_BINS; i++) {
        cout << hOutputHist[i] << " ";
    }
    cout << endl;

    // release memory
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);

    delete[] h_img_data;
    free(hOutputHist);

    return 0;
}