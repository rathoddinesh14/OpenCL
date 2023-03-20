/**
 * Author : Abdelmajid ID ALI
 * Date : 07/10/2021
 * Email : abdelmajid.idali@gmail.com
 */
#define  CL_HPP_MINIMUM_OPENCL_VERSION 120
#define  CL_HPP_TARGET_OPENCL_VERSION 120

#include <iostream>
#include <cl2.hpp>
#include <fstream>

std::string loadKernelSourceFromFile(const char *path);

int main() {


    // list of platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    std::vector<cl::Device> targetDevices;

    std::cout << "Number of platforms: " << platforms.size() << std::endl;

    for(auto platform : platforms) {
        std::cout << "============================================================" << std::endl;
        std::cout << "Platform: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
        std::cout << "Platform vendor: " << platform.getInfo<CL_PLATFORM_VENDOR>() << std::endl;
        std::cout << "Platform version: " << platform.getInfo<CL_PLATFORM_VERSION>() << std::endl;
        std::cout << "Platform profile: " << platform.getInfo<CL_PLATFORM_PROFILE>() << std::endl;
        // std::cout << "Platform extensions: " << platform.getInfo<CL_PLATFORM_EXTENSIONS>() << std::endl;

        // list of devices
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        for(auto device : devices) {
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "Device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
            std::cout << "Device vendor: " << device.getInfo<CL_DEVICE_VENDOR>() << std::endl;
            std::cout << "Device version: " << device.getInfo<CL_DEVICE_VERSION>() << std::endl;
            std::cout << "Device profile: " << device.getInfo<CL_DEVICE_PROFILE>() << std::endl;
            // std::cout << "Device extensions: " << device.getInfo<CL_DEVICE_EXTENSIONS>() << std::endl;
            std::cout << "Device OpenCL C version: " << device.getInfo<CL_DEVICE_OPENCL_C_VERSION>() << std::endl;
            // type
            std::cout << "Device type: " << (device.getInfo<CL_DEVICE_TYPE>() == CL_DEVICE_TYPE_CPU ? "CPU" : "GPU") << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;

            if (device.getInfo<CL_DEVICE_TYPE>() == CL_DEVICE_TYPE_CPU) {
                targetDevices.push_back(device);
            }
        }
        std::cout << "============================================================" << std::endl;
    }

    cl::Context context(targetDevices);

    if (targetDevices.empty()) {
        std::cout << "No device found ! " << std::endl;
        exit(1);
    }

    cl::Device targetDevice = targetDevices[0];

    std::cout << "Selected device : " << std::endl;
    std::cout << "Name : " << targetDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
    std::cout << "Vendor : " << targetDevice.getInfo<CL_DEVICE_VENDOR>() << std::endl;
    std::cout << "Version : " << targetDevice.getInfo<CL_DEVICE_VERSION>() << std::endl;


    const char *path = "./helloworld2.cl";
    std::string source = loadKernelSourceFromFile(path);

    cl::Program program = cl::Program(context, source);

    if (program.build(targetDevices) != CL_SUCCESS) {
        std::cout << "Failed to build source file (" << path << ")" << std::endl;
        auto log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>();

        if (!log.empty()) {
            for (const auto &item: log) {
                std::cout << "Log : " << item.first.getInfo<CL_DEVICE_NAME>() << " : " << item.second.c_str() << std::endl;
            }
        }
        exit(1);
    }

    // number of chars in 'Hello World'
    int count = 13;
    size_t size = sizeof(char) * count;

    // our hello text
    char hostTxt[count];

    // initialize text
    for (int i = 0; i < count; ++i) {
        hostTxt[i] = '-';
    }

    // buffer to get text from device
    //CL_MEM_USE_HOST_PTR
    cl::Buffer textBuffer = cl::Buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, size, &hostTxt);

    cl::CommandQueue commandQueue(context, targetDevice, CL_QUEUE_PROFILING_ENABLE);

    // Create kernel with name of kernel function see 'hello_kernel.cl'
    cl::Kernel kernel(program, "say_hello");
    kernel.setArg(0, textBuffer);

    // enqueue  the kernel  and wait until execution finished
    cl::Event event;
    commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(count), cl::NDRange(1), NULL, &event);
    event.wait();

    unsigned long start_time = event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
    unsigned long end_time = event.getProfilingInfo<CL_PROFILING_COMMAND_END>();
    double milliseconds = ((double) end_time - (double) start_time) / 1000000.0;

    std::cout << "OpenCl Execution time is: " << milliseconds << " ms" << std::endl;


    // read the text buffer from queue
    auto result = commandQueue.enqueueReadBuffer(textBuffer, CL_TRUE, 0, size, &hostTxt);
    if (result != CL_SUCCESS)
        std::cout << "Cannot read buffer" << std::endl;

    std::cout << "Text from device  = " << hostTxt << std::endl;

    return 0;
}

std::string loadKernelSourceFromFile(const char *path) {
    std::ifstream stream(path);
    std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    stream.close();
    return str;
}