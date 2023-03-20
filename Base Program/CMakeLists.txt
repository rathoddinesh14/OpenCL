cmake_minimum_required(VERSION 3.1)

project(HelloWorld)

find_package(OpenCL REQUIRED)

# copy kernel folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/kernels DESTINATION ${CMAKE_BINARY_DIR})

add_executable(HelloWorld
    src/main.cpp
    src/machine.cpp)

target_link_libraries(HelloWorld -lOpenCL)