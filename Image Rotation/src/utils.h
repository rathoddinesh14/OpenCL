#ifndef __UTILS_H__
#define __UTILS_H__

#include <CL/cl.h>
// #include <iostream>
// using namespace std;

const static char *GREENC = "\033[1;32m";
const static char *REDC = "\033[1;31m";
const static char *BLUEC = "\033[1;34m";
const static char *YELLOWC = "\033[1;33m";
const static char *ENDC = "\033[0m";

static void print_image_order(const cl_int &order) {
    /**
     * @brief Construct a new switch object
     * #define CL_R                                        0x10B0
        #define CL_A                                        0x10B1
        #define CL_RG                                       0x10B2
        #define CL_RA                                       0x10B3
        #define CL_RGB                                      0x10B4
        #define CL_RGBA                                     0x10B5
        #define CL_BGRA                                     0x10B6
        #define CL_ARGB                                     0x10B7
        #define CL_INTENSITY                                0x10B8
        #define CL_LUMINANCE                                0x10B9
        #ifdef CL_VERSION_1_1
        #define CL_Rx                                       0x10BA
        #define CL_RGx                                      0x10BB
        #define CL_RGBx                                     0x10BC
        #endif
        #ifdef CL_VERSION_1_2
        #define CL_DEPTH                                    0x10BD
        #define CL_DEPTH_STENCIL                            0x10BE
        #endif
        #ifdef CL_VERSION_2_0
        #define CL_sRGB                                     0x10BF
        #define CL_sRGBx                                    0x10C0
        #define CL_sRGBA                                    0x10C1
        #define CL_sBGRA                                    0x10C2
        #define CL_ABGR                                     0x10C3
        #endif
     * 
     */
    
    cout << "Image order: ";

    switch (order) {
        case CL_R:
            cout << "CL_R" << endl;
            break;
        case CL_A:
            cout << "CL_A" << endl;
            break;
        case CL_RG:
            cout << "CL_RG" << endl;
            break;
        case CL_RA:
            cout << "CL_RA" << endl;
            break;
        case CL_RGB:
            cout << "CL_RGB" << endl;
            break;
        case CL_RGBA:
            cout << "CL_RGBA" << endl;
            break;
        case CL_BGRA:
            cout << "CL_BGRA" << endl;
            break;
        case CL_ARGB:
            cout << "CL_ARGB" << endl;
            break;
        case CL_INTENSITY:
            cout << "CL_INTENSITY" << endl;
            break;
        case CL_LUMINANCE:
            cout << "CL_LUMINANCE" << endl;
            break;
        case CL_Rx:
            cout << "CL_Rx" << endl;
            break;
        case CL_RGx:
            cout << "CL_RGx" << endl;
            break;
        case CL_RGBx:
            cout << "CL_RGBx" << endl;
            break;
        case CL_DEPTH:
            cout << "CL_DEPTH" << endl;
            break;
        case CL_DEPTH_STENCIL:
            cout << "CL_DEPTH_STENCIL" << endl;
            break;
        case CL_sRGB:
            cout << "CL_sRGB" << endl;
            break;
        case CL_sRGBx:
            cout << "CL_sRGBx" << endl;
            break;
        case CL_sRGBA:
            cout << "CL_sRGBA" << endl;
            break;
        case CL_sBGRA:
            cout << "CL_sBGRA" << endl;
            break;
        case CL_ABGR:
            cout << "CL_ABGR" << endl;
            break;
        default:
            cout << "Unknown image order" << endl;
            break;
    }
}

static void print_image_channel_type(const cl_int &c_type) {
    /**
     * @brief 
     *  cl_channel_type
        #define CL_SNORM_INT8                               0x10D0
        #define CL_SNORM_INT16                              0x10D1
        #define CL_UNORM_INT8                               0x10D2
        #define CL_UNORM_INT16                              0x10D3
        #define CL_UNORM_SHORT_565                          0x10D4
        #define CL_UNORM_SHORT_555                          0x10D5
        #define CL_UNORM_INT_101010                         0x10D6
        #define CL_SIGNED_INT8                              0x10D7
        #define CL_SIGNED_INT16                             0x10D8
        #define CL_SIGNED_INT32                             0x10D9
        #define CL_UNSIGNED_INT8                            0x10DA
        #define CL_UNSIGNED_INT16                           0x10DB
        #define CL_UNSIGNED_INT32                           0x10DC
        #define CL_HALF_FLOAT                               0x10DD
        #define CL_FLOAT                                    0x10DE
        #ifdef CL_VERSION_1_2
        #define CL_UNORM_INT24                              0x10DF
        #endif
        #ifdef CL_VERSION_2_1
        #define CL_UNORM_INT_101010_2                       0x10E0
        #endif
     * 
     */

    cout << "Image channel type: ";

    switch (c_type) {
        case CL_SNORM_INT8:
            cout << "CL_SNORM_INT8" << endl;
            break;
        case CL_SNORM_INT16:
            cout << "CL_SNORM_INT16" << endl;
            break;
        case CL_UNORM_INT8:
            cout << "CL_UNORM_INT8" << endl;
            break;
        case CL_UNORM_INT16:
            cout << "CL_UNORM_INT16" << endl;
            break;
        case CL_UNORM_SHORT_565:
            cout << "CL_UNORM_SHORT_565" << endl;
            break;
        case CL_UNORM_SHORT_555:
            cout << "CL_UNORM_SHORT_555" << endl;
            break;
        case CL_UNORM_INT_101010:
            cout << "CL_UNORM_INT_101010" << endl;
            break;
        case CL_SIGNED_INT8:
            cout << "CL_SIGNED_INT8" << endl;
            break;
        case CL_SIGNED_INT16:
            cout << "CL_SIGNED_INT16" << endl;
            break;
        case CL_SIGNED_INT32:
            cout << "CL_SIGNED_INT32" << endl;
            break;
        case CL_UNSIGNED_INT8:
            cout << "CL_UNSIGNED_INT8" << endl;
            break;
        case CL_UNSIGNED_INT16:
            cout << "CL_UNSIGNED_INT16" << endl;
            break;
        case CL_UNSIGNED_INT32:
            cout << "CL_UNSIGNED_INT32" << endl;
            break;
        case CL_HALF_FLOAT:
            cout << "CL_HALF_FLOAT" << endl;
            break;
        case CL_FLOAT:
            cout << "CL_FLOAT" << endl;
            break;
        case CL_UNORM_INT24:
            cout << "CL_UNORM_INT24" << endl;
            break;
        default:
            cout << "Unknown image channel type" << endl;
            break;
    }

}

static void print_detailed_error(const cl_int &status, const char *msg) {

    /**
     * @brief Construct a new switch object
     * 
        #define CL_SUCCESS                                  0
        #define CL_DEVICE_NOT_FOUND                         -1
        #define CL_DEVICE_NOT_AVAILABLE                     -2
        #define CL_COMPILER_NOT_AVAILABLE                   -3
        #define CL_MEM_OBJECT_ALLOCATION_FAILURE            -4
        #define CL_OUT_OF_RESOURCES                         -5
        #define CL_OUT_OF_HOST_MEMORY                       -6
        #define CL_PROFILING_INFO_NOT_AVAILABLE             -7
        #define CL_MEM_COPY_OVERLAP                         -8
        #define CL_IMAGE_FORMAT_MISMATCH                    -9
        #define CL_IMAGE_FORMAT_NOT_SUPPORTED               -10
        #define CL_BUILD_PROGRAM_FAILURE                    -11
        #define CL_MAP_FAILURE                              -12
        #ifdef CL_VERSION_1_1
        #define CL_MISALIGNED_SUB_BUFFER_OFFSET             -13
        #define CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST -14
        #endif
        #ifdef CL_VERSION_1_2
        #define CL_COMPILE_PROGRAM_FAILURE                  -15
        #define CL_LINKER_NOT_AVAILABLE                     -16
        #define CL_LINK_PROGRAM_FAILURE                     -17
        #define CL_DEVICE_PARTITION_FAILED                  -18
        #define CL_KERNEL_ARG_INFO_NOT_AVAILABLE            -19
        #endif

        #define CL_INVALID_VALUE                            -30
        #define CL_INVALID_DEVICE_TYPE                      -31
        #define CL_INVALID_PLATFORM                         -32
        #define CL_INVALID_DEVICE                           -33
        #define CL_INVALID_CONTEXT                          -34
        #define CL_INVALID_QUEUE_PROPERTIES                 -35
        #define CL_INVALID_COMMAND_QUEUE                    -36
        #define CL_INVALID_HOST_PTR                         -37
        #define CL_INVALID_MEM_OBJECT                       -38
        #define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR          -39
        #define CL_INVALID_IMAGE_SIZE                       -40
        #define CL_INVALID_SAMPLER                          -41
        #define CL_INVALID_BINARY                           -42
        #define CL_INVALID_BUILD_OPTIONS                    -43
        #define CL_INVALID_PROGRAM                          -44
        #define CL_INVALID_PROGRAM_EXECUTABLE               -45
        #define CL_INVALID_KERNEL_NAME                      -46
        #define CL_INVALID_KERNEL_DEFINITION                -47
        #define CL_INVALID_KERNEL                           -48
        #define CL_INVALID_ARG_INDEX                        -49
        #define CL_INVALID_ARG_VALUE                        -50
        #define CL_INVALID_ARG_SIZE                         -51
        #define CL_INVALID_KERNEL_ARGS                      -52
        #define CL_INVALID_WORK_DIMENSION                   -53
        #define CL_INVALID_WORK_GROUP_SIZE                  -54
        #define CL_INVALID_WORK_ITEM_SIZE                   -55
        #define CL_INVALID_GLOBAL_OFFSET                    -56
        #define CL_INVALID_EVENT_WAIT_LIST                  -57
        #define CL_INVALID_EVENT                            -58
        #define CL_INVALID_OPERATION                        -59
        #define CL_INVALID_GL_OBJECT                        -60
        #define CL_INVALID_BUFFER_SIZE                      -61
        #define CL_INVALID_MIP_LEVEL                        -62
        #define CL_INVALID_GLOBAL_WORK_SIZE                 -63
        #ifdef CL_VERSION_1_1
        #define CL_INVALID_PROPERTY                         -64
        #endif
        #ifdef CL_VERSION_1_2
        #define CL_INVALID_IMAGE_DESCRIPTOR                 -65
        #define CL_INVALID_COMPILER_OPTIONS                 -66
        #define CL_INVALID_LINKER_OPTIONS                   -67
        #define CL_INVALID_DEVICE_PARTITION_COUNT           -68
        #endif
        #ifdef CL_VERSION_2_0
        #define CL_INVALID_PIPE_SIZE                        -69
        #define CL_INVALID_DEVICE_QUEUE                     -70
        #endif
        #ifdef CL_VERSION_2_2
        #define CL_INVALID_SPEC_ID                          -71
        #define CL_MAX_SIZE_RESTRICTION_EXCEEDED            -72
        #endif
     */

    switch (status) {
        case CL_SUCCESS:
            cout << "CL_SUCCESS" << endl;
            break;
        case CL_DEVICE_NOT_FOUND:
            cout << "CL_DEVICE_NOT_FOUND" << endl;
            break;
        case CL_DEVICE_NOT_AVAILABLE:
            cout << "CL_DEVICE_NOT_AVAILABLE" << endl;
            break;
        case CL_COMPILER_NOT_AVAILABLE:
            cout << "CL_COMPILER_NOT_AVAILABLE" << endl;
            break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE:
            cout << "CL_MEM_OBJECT_ALLOCATION_FAILURE" << endl;
            break;
        case CL_OUT_OF_RESOURCES:
            cout << "CL_OUT_OF_RESOURCES" << endl;
            break;
        case CL_OUT_OF_HOST_MEMORY:
            cout << "CL_OUT_OF_HOST_MEMORY" << endl;
            break;
        case CL_PROFILING_INFO_NOT_AVAILABLE:
            cout << "CL_PROFILING_INFO_NOT_AVAILABLE" << endl;
            break;
        case CL_MEM_COPY_OVERLAP:
            cout << "CL_MEM_COPY_OVERLAP" << endl;
            break;
        case CL_IMAGE_FORMAT_MISMATCH:
            cout << "CL_IMAGE_FORMAT_MISMATCH" << endl;
            break;
        case CL_IMAGE_FORMAT_NOT_SUPPORTED:
            cout << "CL_IMAGE_FORMAT_NOT_SUPPORTED" << endl;
            break;
        case CL_BUILD_PROGRAM_FAILURE:
            cout << "CL_BUILD_PROGRAM_FAILURE" << endl;
            break;
        case CL_MAP_FAILURE:
            cout << "CL_MAP_FAILURE" << endl;
            break;
        case CL_MISALIGNED_SUB_BUFFER_OFFSET:
            cout << "CL_MISALIGNED_SUB_BUFFER_OFFSET" << endl;
            break;
        case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
            cout << "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST" << endl;
            break;
        case CL_COMPILE_PROGRAM_FAILURE:
            cout << "CL_COMPILE_PROGRAM_FAILURE" << endl;
            break;
        case CL_LINKER_NOT_AVAILABLE:
            cout << "CL_LINKER_NOT_AVAILABLE" << endl;
            break;
        case CL_LINK_PROGRAM_FAILURE:
            cout << "CL_LINK_PROGRAM_FAILURE" << endl;
            break;
        case CL_DEVICE_PARTITION_FAILED:
            cout << "CL_DEVICE_PARTITION_FAILED" << endl;
            break;
        case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
            cout << "CL_KERNEL_ARG_INFO_NOT_AVAILABLE" << endl;
            break;
        case CL_INVALID_VALUE:
            cout << "CL_INVALID_VALUE" << endl;
            break;
        case CL_INVALID_DEVICE_TYPE:
            cout << "CL_INVALID_DEVICE_TYPE" << endl;
            break;
        case CL_INVALID_PLATFORM:
            cout << "CL_INVALID_PLATFORM" << endl;
            break;
        case CL_INVALID_DEVICE:
            cout << "CL_INVALID_DEVICE" << endl;
            break;
        case CL_INVALID_CONTEXT:
            cout << "CL_INVALID_CONTEXT" << endl;
            break;
        case CL_INVALID_QUEUE_PROPERTIES:
            cout << "CL_INVALID_QUEUE_PROPERTIES" << endl;
            break;
        case CL_INVALID_COMMAND_QUEUE:
            cout << "CL_INVALID_COMMAND_QUEUE" << endl;
            break;
        case CL_INVALID_HOST_PTR:
            cout << "CL_INVALID_HOST_PTR" << endl;
            break;
        case CL_INVALID_MEM_OBJECT:
            cout << "CL_INVALID_MEM_OBJECT" << endl;
            break;
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
            cout << "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR" << endl;
            break;
        case CL_INVALID_IMAGE_SIZE:
            cout << "CL_INVALID_IMAGE_SIZE" << endl;
            break;
        case CL_INVALID_SAMPLER:
            cout << "CL_INVALID_SAMPLER" << endl;
            break;
        case CL_INVALID_BINARY:
            cout << "CL_INVALID_BINARY" << endl;
            break;
        case CL_INVALID_BUILD_OPTIONS:
            cout << "CL_INVALID_BUILD_OPTIONS" << endl;
            break;
        case CL_INVALID_PROGRAM:
            cout << "CL_INVALID_PROGRAM" << endl;
            break;
        case CL_INVALID_PROGRAM_EXECUTABLE:
            cout << "CL_INVALID_PROGRAM_EXECUTABLE" << endl;
            break;
        case CL_INVALID_KERNEL_NAME:
            cout << "CL_INVALID_KERNEL_NAME" << endl;
            break;
        case CL_INVALID_KERNEL_DEFINITION:
            cout << "CL_INVALID_KERNEL_DEFINITION" << endl;
            break;
        case CL_INVALID_KERNEL:
            cout << "CL_INVALID_KERNEL" << endl;
            break;
        case CL_INVALID_ARG_INDEX:
            cout << "CL_INVALID_ARG_INDEX" << endl;
            break;
        case CL_INVALID_ARG_VALUE:
            cout << "CL_INVALID_ARG_VALUE" << endl;
            break;
        case CL_INVALID_ARG_SIZE:
            cout << "CL_INVALID_ARG_SIZE" << endl;
            break;
        case CL_INVALID_KERNEL_ARGS:
            cout << "CL_INVALID_KERNEL_ARGS" << endl;
            break;
        case CL_INVALID_WORK_DIMENSION:
            cout << "CL_INVALID_WORK_DIMENSION" << endl;
            break;
        case CL_INVALID_WORK_GROUP_SIZE:
            cout << "CL_INVALID_WORK_GROUP_SIZE" << endl;
            break;
        case CL_INVALID_WORK_ITEM_SIZE:
            cout << "CL_INVALID_WORK_ITEM_SIZE" << endl;
            break;
        case CL_INVALID_GLOBAL_OFFSET:
            cout << "CL_INVALID_GLOBAL_OFFSET" << endl;
            break;
        case CL_INVALID_EVENT_WAIT_LIST:
            cout << "CL_INVALID_EVENT_WAIT_LIST" << endl;
            break;
        case CL_INVALID_EVENT:
            cout << "CL_INVALID_EVENT" << endl;
            break;
        case CL_INVALID_OPERATION:
            cout << "CL_INVALID_OPERATION" << endl;
            break;
        case CL_INVALID_GL_OBJECT:
            cout << "CL_INVALID_GL_OBJECT" << endl;
            break;
        case CL_INVALID_BUFFER_SIZE:
            cout << "CL_INVALID_BUFFER_SIZE" << endl;
            break;
        case CL_INVALID_MIP_LEVEL:
            cout << "CL_INVALID_MIP_LEVEL" << endl;
            break;
        case CL_INVALID_GLOBAL_WORK_SIZE:
            cout << "CL_INVALID_GLOBAL_WORK_SIZE" << endl;
            break;
        case CL_INVALID_PROPERTY:
            cout << "CL_INVALID_PROPERTY" << endl;
            break;
        case CL_INVALID_IMAGE_DESCRIPTOR:
            cout << "CL_INVALID_IMAGE_DESCRIPTOR" << endl;
            break;
        case CL_INVALID_COMPILER_OPTIONS:
            cout << "CL_INVALID_COMPILER_OPTIONS" << endl;
            break;
        case CL_INVALID_LINKER_OPTIONS:
            cout << "CL_INVALID_LINKER_OPTIONS" << endl;
            break;
        case CL_INVALID_DEVICE_PARTITION_COUNT:
            cout << "CL_INVALID_DEVICE_PARTITION_COUNT" << endl;
            break;
        default:
            cout << "UNKNOWN ERROR" << endl;
            break;
    }
    cout << "status code : " << status << endl;
}

static void check_point(const cl_int status, const char* msg) {
    if (status != CL_SUCCESS) {
        print_detailed_error(status, msg);
        exit(EXIT_FAILURE);
    }
}

#endif // __UTILS_H__