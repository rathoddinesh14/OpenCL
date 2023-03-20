#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include "machine.h"
#include <iostream>
#include <vector>

using namespace std;



int main() {

    const int num_elements = 1024;

    // datasize
    size_t datasize = sizeof(int) * num_elements;

    cout << "datasize: " << datasize << endl;

    // host data
    int *h_a = new int[num_elements];
    int *h_b = new int[num_elements];
    int *h_c = new int[num_elements];

    // init host data
    for (int i = 0; i < num_elements; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    Machine machine;
    machine.create_single_context();
    
    // create buffer
    cl_int status;
    cl_mem d_a = clCreateBuffer(machine.get_context(), CL_MEM_READ_ONLY, datasize, NULL, &status);
    cl_mem d_b = clCreateBuffer(machine.get_context(), CL_MEM_READ_ONLY, datasize, NULL, &status);
    cl_mem d_c = clCreateBuffer(machine.get_context(), CL_MEM_WRITE_ONLY, datasize, NULL, &status);

    machine.create_cmd_queue();

    // write data to device
    status = clEnqueueWriteBuffer(machine.get_cmd_queue(), d_a, CL_FALSE, 0, datasize, h_a, 0, NULL, NULL);
    status = clEnqueueWriteBuffer(machine.get_cmd_queue(), d_b, CL_FALSE, 0, datasize, h_b, 0, NULL, NULL);

    // create program
    machine.create_build_program("kernels/vecadd.cl");

    // add kernel
    machine.add_kernel("vecadd");

    // get kernel
    cl_kernel kernel = machine.get_kernel("vecadd");

    // set kernel arguments
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &d_b);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);

    // set work size and index
    size_t indexSpaceSize[1] = {num_elements}, workGroupSize[1] = {64};

    // execute kernel
    status = clEnqueueNDRangeKernel(machine.get_cmd_queue(), kernel, 1, NULL, indexSpaceSize, workGroupSize, 0, NULL, NULL);

    // read data from device
    status = clEnqueueReadBuffer(machine.get_cmd_queue(), d_c, CL_TRUE, 0, datasize, h_c, 0, NULL, NULL);

    // print result
    for (int i = 0; i < num_elements; i++) {
        cout << h_c[i] << " ";
    }
    cout << endl;

    // release memory
    clReleaseMemObject(d_a);
    clReleaseMemObject(d_b);
    clReleaseMemObject(d_c);

    delete[] h_a;
    delete[] h_b;
    delete[] h_c;

    return 0;
}