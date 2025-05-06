cmake_minimum_required(VERSION 3.16)

project(Cryptarithm_Cmd VERSION 0.1 LANGUAGES CXX)

add_executable(cryptarithm_cmd
    cmd_main.cpp
)

# set(CMAKE_CXX_COMPILER, "C:\\Program Files (x86)\\msys64\\mingw64\\bin\\g++.exe")
# set(CMAKE_CXX_FLAGS_DEBUG "/Z7")

# Use the "backend" library
add_subdirectory(../backend ./backend_copy)

target_link_libraries(cryptarithm_cmd PRIVATE 
    backend
)