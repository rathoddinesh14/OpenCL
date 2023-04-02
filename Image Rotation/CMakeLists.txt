cmake_minimum_required(VERSION 3.1)

project(ImageRotation)

find_package(OpenCL REQUIRED)

# define cl version
add_definitions(-DCL_TARGET_OPENCL_VERSION=200)

# include thirdparty folder
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

# copy kernel folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/kernels DESTINATION ${CMAKE_BINARY_DIR})

# copy assets folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(ImageRotation
    src/main.cpp
    src/machine.cpp
    thirdparty/stb_image.cpp
    thirdparty/stb_image_write.cpp)

target_link_libraries(ImageRotation -lOpenCL)