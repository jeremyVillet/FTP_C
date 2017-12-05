cmake_minimum_required(VERSION 3.7)
project(supSharingClient)

set(CMAKE_C_STANDARD 99)

link_libraries(ws2_32 wsock32)

set(SOURCE_FILES main.c main.h)
add_executable(supSharingClient ${SOURCE_FILES})