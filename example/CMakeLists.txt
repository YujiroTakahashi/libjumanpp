cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(jumanpp-example)

set (jumanpp-example_VERSION_MAJOR 0)
set (jumanpp-example_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads)
find_library(pathie-shared NAMES libpathie.so PATHS /usr/lib /usr/local/lib)
find_library(jumanpp-shared NAMES libjumanpp.so PATHS /usr/lib /usr/local/lib)

add_subdirectory(src)
