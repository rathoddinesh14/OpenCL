#define __CL_ENABLE_EXCEPTIONS

#include <cl.hpp>
#include <assert.h>
#include <iostream>

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

    

}