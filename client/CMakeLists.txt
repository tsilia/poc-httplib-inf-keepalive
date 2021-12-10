cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(..)

FIND_PACKAGE(Threads REQUIRED)
add_executable(client main.cpp)
TARGET_LINK_LIBRARIES(client ${CMAKE_THREAD_LIBS_INIT})
