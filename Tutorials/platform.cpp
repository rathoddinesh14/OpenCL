#define __CL_ENABLE_EXCEPTIONS

#include <cl2.hpp>
#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // assert
    assert(platforms.size() > 0);

    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    // assert
    assert(devices.size() > 0);

    for (auto device : devices)
    {
        auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
        auto name = device.getInfo<CL_DEVICE_NAME>();
        auto version = device.getInfo<CL_DEVICE_VERSION>();
        auto driverVersion = device.getInfo<CL_DRIVER_VERSION>();
        auto profile = device.getInfo<CL_DEVICE_PROFILE>();

        std::cout << "Vendor: " << vendor << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Version: " << version << std::endl;
        std::cout << "Driver version: " << driverVersion << std::endl;
        std::cout << "Profile: " << profile << std::endl;
    }

    // auto device = devices.front();
    std::ifstream helloworld("helloworld.cl");
    std::string src(std::istreambuf_iterator<char>(helloworld), (std::istreambuf_iterator<char>()));

    cl::Program::Sources sources(1, src.c_str());

    cl::Context context(devices);

    cl::Program program(context, sources);

    try
    {
        program.build(devices);
    }
    catch (cl::Error err)
    {
        std::cout << "Build Status: " << program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(devices[0]) << std::endl;
        std::cout << "Build Options:\t" << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(devices[0]) << std::endl;
        std::cout << "Build Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]) << std::endl;
        throw err;
    }

    try
    {
        char buffer[16];
        cl::Buffer memBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buffer));

        cl::Kernel kernel(program, "hello");

        // kernel.setArg(0, memBuffer);

        // cl::CommandQueue queue(context, devices[0]);

        // // enqueue task
        // queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NullRange);
        // // enqueue read buffer
        // queue.enqueueReadBuffer(memBuffer, CL_TRUE, 0, sizeof(buffer), buffer);

        // std::cout << "Result: " << buffer << std::endl;
    }
    catch (cl::Error err)
    {
        std::cerr << "Error: " << err.what() << "(" << err.err() << ")" << std::endl;
        throw err;
    }
}