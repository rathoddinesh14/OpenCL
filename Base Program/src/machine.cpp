#include "machine.h"
#include "utils.h"

void Machine::print_platform_info(const cl_platform_id &platform) {
    // get platform name
    size_t platform_name_size;
    clGetPlatformInfo(platform, CL_PLATFORM_NAME, 0, NULL, &platform_name_size);
    char *platform_name = new char[platform_name_size];
    clGetPlatformInfo(platform, CL_PLATFORM_NAME, platform_name_size, platform_name, NULL);

    // get platform vendor
    size_t platform_vendor_size;
    clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, NULL, &platform_vendor_size);
    char *platform_vendor = new char[platform_vendor_size];
    clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, platform_vendor_size, platform_vendor, NULL);

    // get platform version
    size_t platform_version_size;
    clGetPlatformInfo(platform, CL_PLATFORM_VERSION, 0, NULL, &platform_version_size);
    char *platform_version = new char[platform_version_size];
    clGetPlatformInfo(platform, CL_PLATFORM_VERSION, platform_version_size, platform_version, NULL);

    // print platform info
    cout << "------------------- platform info -------------------" << endl;
    cout << "platform id: " << platform << endl;
    cout << "platform name: " << platform_name << endl;
    cout << "platform vendor: " << platform_vendor << endl;
    cout << "platform version: " << platform_version << endl;
    cout << "-----------------------------------------------------" << endl;

    // free memory
    delete[] platform_name;
    delete[] platform_vendor;
    delete[] platform_version;
}

void Machine::print_device_info(const cl_device_id &device) {
    // get device name
    size_t device_name_size;
    clGetDeviceInfo(device, CL_DEVICE_NAME, 0, NULL, &device_name_size);
    char *device_name = new char[device_name_size];
    clGetDeviceInfo(device, CL_DEVICE_NAME, device_name_size, device_name, NULL);

    // get device vendor
    size_t device_vendor_size;
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, 0, NULL, &device_vendor_size);
    char *device_vendor = new char[device_vendor_size];
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, device_vendor_size, device_vendor, NULL);

    // get device version
    size_t device_version_size;
    clGetDeviceInfo(device, CL_DEVICE_VERSION, 0, NULL, &device_version_size);
    char *device_version = new char[device_version_size];
    clGetDeviceInfo(device, CL_DEVICE_VERSION, device_version_size, device_version, NULL);

    // print device info
    cout << "------------------- device info -------------------" << endl;
    cout << "device id: " << device << endl;
    cout << "device name: " << device_name << endl;
    cout << "device vendor: " << device_vendor << endl;
    cout << "device version: " << device_version << endl;
    cout << "---------------------------------------------------" << endl;

    // free memory
    delete[] device_name;
    delete[] device_vendor;
    delete[] device_version;
}

Machine::Machine() {

    m_context = NULL;

    // get all platforms
    cl_int status;
    status = clGetPlatformIDs(0, NULL, &m_num_platforms);

    m_platforms = new platform[m_num_platforms];

    // get platform ids
    cl_platform_id *platform_ids = new cl_platform_id[m_num_platforms];
    status = clGetPlatformIDs(m_num_platforms, platform_ids, NULL);

    for (int i = 0; i < m_num_platforms; i++) {
        m_platforms[i].id = platform_ids[i];

        // get number of devices
        status = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_ALL, 0, NULL, &m_platforms[i].num_devices);

        // get device ids
        m_platforms[i].devices = new cl_device_id[m_platforms[i].num_devices];
        status = clGetDeviceIDs(platform_ids[i], CL_DEVICE_TYPE_ALL, m_platforms[i].num_devices, m_platforms[i].devices, NULL);
    }

    // free memory
    delete[] platform_ids;
}

Machine::~Machine() {
    
    for (int i = 0; i < m_kernels.size(); i++) {
        if (m_kernels[i] != NULL)
            clReleaseKernel(m_kernels[i]);
    }

    if (m_program != NULL)
        clReleaseProgram(m_program);
    
    if (m_cmd_queue != NULL)
        clReleaseCommandQueue(m_cmd_queue);
    
    delete[] m_platforms;

    if (m_context != NULL)
        clReleaseContext(m_context);
}

cl_uint Machine::get_num_platforms() {
    return m_num_platforms;
}

void Machine::print_platform_and_device_info() {
    cout << "num_platforms: " << m_num_platforms << endl;

    for (int i = 0; i < m_num_platforms; i++) {

        cout << "=====================================================" << endl;

        print_platform_info(m_platforms[i].id);

        for (int j = 0; j < m_platforms[i].num_devices; j++)
        {
            print_device_info(m_platforms[i].devices[j]);
        }

        cout << "=====================================================" << endl;
    }
}

void Machine::create_single_context() {

    // iterate through all platforms
    for (int i = 0; i < m_num_platforms; i++) {
        cout << GREENC << "@@@@@@@@@@@@ platform id: " << i << " @@@@@@@@@@@@" << ENDC << endl;
        print_platform_info(m_platforms[i].id);
    }
    // select platform id in red color
    cout << REDC << "select platform id: " << ENDC << endl;
    cin >> m_platform_id;

    // iterate through all devices
    for (int i = 0; i < m_platforms[m_platform_id].num_devices; i++) {
        // print choose device id
        cout << GREENC << "@@@@@@@@@@@@ device id: " << i << " @@@@@@@@@@@@" << ENDC << endl;
        print_device_info(m_platforms[m_platform_id].devices[i]);
    }
    // select device id in red color
    cout << REDC << "select device id: " << ENDC << endl;
    cin >> m_device_id;

    cl_int status;

    // create context
    m_context = clCreateContext(NULL, 1, &m_platforms[m_platform_id].devices[m_device_id], NULL, NULL, &status);

    // print error message
    if (status != CL_SUCCESS) {
        cout << "error: clCreateContext" << endl;
        exit(1);
    }
}

void Machine::create_cmd_queue() {
    
    if (m_context == NULL) {
        cout << "error: m_context is NULL" << endl;
        exit(1);
    }

    cl_int status;

    // create command queue
    m_cmd_queue = clCreateCommandQueue(m_context, m_platforms[m_platform_id].devices[m_device_id], 0, &status);

    // print error message
    if (status != CL_SUCCESS) {
        cout << "error: clCreateCommandQueue" << endl;
        exit(1);
    }
}

void Machine::print_context_info() {
    // get context info
    size_t context_info_size = 0;
    if (m_context == NULL) {
        cout << "error: m_context is NULL" << endl;
        return;
    }
    
    // get choosen device id
    cl_device_id device_id;
    clGetContextInfo(m_context, CL_CONTEXT_DEVICES, sizeof(cl_device_id), &device_id, NULL);

    // print context info
    cout << "------------------- context info -------------------" << endl;
    cout << "context id: " << m_context << endl;
    cout << "device id: " << device_id << endl;
    cout << "----------------------------------------------------" << endl;
}

cl_context Machine::get_context() {
    return m_context;
}

cl_command_queue Machine::get_cmd_queue() {
    return m_cmd_queue;
}

void Machine::create_build_program(const char *filename) {

    if (m_context == NULL) {
        cout << "error: m_context is NULL" << endl;
        exit(1);
    }

    // reading file into buffer
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        cout << "error: fopen" << endl;
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    rewind(fp);

    char *buffer = new char[file_size + 1];
    fread(buffer, file_size, 1, fp);
    buffer[file_size] = '\0';
    fclose(fp);

    // create program
    cl_int status;
    m_program = clCreateProgramWithSource(m_context, 1, (const char **)&buffer, NULL, &status);

    // print error message
    if (status != CL_SUCCESS) {
        cout << "error: clCreateProgramWithSource" << endl;
        exit(1);
    }

    // build program
    status = clBuildProgram(m_program, 1, &m_platforms[m_platform_id].devices[m_device_id], NULL, NULL, NULL);

    // print error message
    if (status != CL_SUCCESS) {
        cout << "error: clBuildProgram" << endl;
        exit(1);
    }
}

void Machine::add_kernel(const char *kernel_name) {
    cl_int status;

    // create kernel
    cl_kernel kernel = clCreateKernel(m_program, kernel_name, &status);

    // print error message
    if (status != CL_SUCCESS) {
        cout << "error: clCreateKernel" << endl;
        exit(1);
    }

    // add kernel to vector
    m_kernels.push_back(kernel);
}

cl_kernel Machine::get_kernel(const char *kernel_name) {
    for (int i = 0; i < m_kernels.size(); i++) {
        char cur_kernel_name[100];

        // get kernel name
        clGetKernelInfo(m_kernels[i], CL_KERNEL_FUNCTION_NAME, sizeof(cur_kernel_name), cur_kernel_name, NULL);

        if (strcmp(kernel_name, cur_kernel_name) == 0) {
            return m_kernels[i];
        }
    }
    return NULL;
}
