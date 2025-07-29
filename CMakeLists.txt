cmake_minimum_required(VERSION 3.10)

project(BigIntCpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(safe_factorial safe_factorial.cpp)
add_executable(teste teste.cpp)
