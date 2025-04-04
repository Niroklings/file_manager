cmake_minimum_required(VERSION 3.10)
project(FileManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(file_manager src/main.cpp src/FileManager.cpp)