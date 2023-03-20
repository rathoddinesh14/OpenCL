cmake_minimum_required(VERSION 3.1)

project(HelloWorld)

find_package(OpenCL REQUIRED)

add_executable(HelloWorld
    src/main.cpp
    src/machine.cpp)

target_link_libraries(HelloWorld -lOpenCL)