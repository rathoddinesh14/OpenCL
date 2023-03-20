#ifndef MACHIINE_H
#define MACHIINE_H

#include <CL/cl.h>
#include <iostream>

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

    void print_context_info();

};


#endif // MACHIINE_H

