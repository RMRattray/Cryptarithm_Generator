cmake_minimum_required(VERSION 3.16)

project(Cryptarithm_Cmd VERSION 0.1 LANGUAGES CXX)

add_executable(cryptarithm_cmd
    cmd_main.cpp
)

# Use the "backend" library
add_subdirectory(../backend)
target_link_libraries(cryptarithm_cmd PRIVATE 
    backend
)