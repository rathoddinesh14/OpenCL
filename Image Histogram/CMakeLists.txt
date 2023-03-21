cmake_minimum_required(VERSION 3.1)

project(ImageHistogram)

find_package(OpenCL REQUIRED)

# include thirdparty folder
include_directories(${CMAKE_SOURCE_DIR}/thirdparty)

# copy kernel folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/kernels DESTINATION ${CMAKE_BINARY_DIR})

# copy assets folder to build folder
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(ImageHistogram
    src/main.cpp
    src/machine.cpp
    thirdparty/stb_image.cpp)

target_link_libraries(ImageHistogram -lOpenCL)