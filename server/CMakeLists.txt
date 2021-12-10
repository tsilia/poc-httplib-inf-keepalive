cmake_minimum_required(VERSION 3.5)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(..)

FIND_PACKAGE(Threads REQUIRED)
add_executable(server main.cpp)
TARGET_LINK_LIBRARIES(server ${CMAKE_THREAD_LIBS_INIT})
