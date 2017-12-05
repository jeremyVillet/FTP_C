cmake_minimum_required(VERSION 3.7)
project(supSharingServer)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c main.h)
link_libraries(ws2_32 wsock32)
add_executable(supSharingServer ${SOURCE_FILES})