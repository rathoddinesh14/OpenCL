cmake_minimum_required(VERSION 3.10)

# set the project name
project(HelloWorld)

# add the executable
add_executable(HelloWorld main.cpp)

# add the library
add_library(hello hello.cpp)

# add the executable
add_executable(HelloWorld main.cpp)

# link the library
target_link_libraries(HelloWorld hello)