#ifndef MACHIINE_H
#define MACHIINE_H

#include <CL/cl.h>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


class Machine {

    struct platform {
        cl_platform_id id;
        cl_uint num_devices;
        cl_device_id *devices;

        platform() {
            num_devices = 0;
            devices = NULL;
        }
    };

    cl_uint m_num_platforms;
    platform *m_platforms;

    // context
    cl_context m_context;

    // command queue
    cl_command_queue m_cmd_queue;

    // program
    cl_program m_program;

    // kernel list
    vector<cl_kernel> m_kernels;

    // select platform and device
    int m_platform_id;
    int m_device_id;

    void print_platform_info(const cl_platform_id &platform);

    void print_device_info(const cl_device_id &device);

public:
    Machine();

    ~Machine();

    cl_uint get_num_platforms();

    void print_platform_and_device_info();

    void create_single_context();

    void create_cmd_queue();

    void print_context_info();

    cl_context get_context();

    cl_command_queue get_cmd_queue();

    void create_build_program(const char *filename);

    void add_kernel(const char *kernel_name);

    cl_kernel get_kernel(const char *kernel_name);
};


#endif // MACHIINE_H

