cmake_minimum_required(VERSION 3.16)
project(Composite)

add_executable(composite_design_pattern src/main.cpp src/file.cpp)
target_include_directories(composite_design_pattern PRIVATE ./include)
