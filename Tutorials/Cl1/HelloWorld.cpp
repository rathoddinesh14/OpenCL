#define __CL_ENABLE_EXCEPTIONS

#include <cl.hpp>
#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    std::vector<cl::Device> targetDevices;

    // assert
    assert(platforms.size() > 0);

    for (auto platform : platforms)
    {
        std::cout << "====================================" << std::endl;
        auto vendor = platform.getInfo<CL_PLATFORM_VENDOR>();
        auto name = platform.getInfo<CL_PLATFORM_NAME>();
        auto version = platform.getInfo<CL_PLATFORM_VERSION>();
        auto profile = platform.getInfo<CL_PLATFORM_PROFILE>();

        std::cout << "Vendor: " << vendor << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Version: " << version << std::endl;
        std::cout << "Profile: " << profile << std::endl;

        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        // assert
        assert(devices.size() > 0);
        for (auto device : devices)
        {
            std::cout << "------------------------------------" << std::endl;
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
            std::cout << "Device type: " << device.getInfo<CL_DEVICE_TYPE>() << std::endl;

            // check if device is a GPU
            if (device.getInfo<CL_DEVICE_TYPE>() == CL_DEVICE_TYPE_CPU)
            {
                targetDevices.push_back(device);
            }
            std::cout << "------------------------------------" << std::endl;
        }
        // print ========================================
        std::cout << "====================================" << std::endl;
    }

    std::ifstream file("helloworld.cl");
    std::string src(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
    cl::Context context(targetDevices);
    cl::Program program(context, sources);

    auto err = program.build(targetDevices);

    char buf[16];
    cl::Buffer memBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
    cl::Kernel kernel(program, "HelloWorld", &err);
    kernel.setArg(0, memBuffer);

    cl::CommandQueue queue(context, targetDevices.front());
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(memBuffer, CL_TRUE, 0, sizeof(buf), buf);

    std::cout << "Result: " << buf << std::endl;
}