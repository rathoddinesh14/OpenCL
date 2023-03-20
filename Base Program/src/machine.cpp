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
    delete[] m_platforms;
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
