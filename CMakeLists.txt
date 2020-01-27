cmake_minimum_required(VERSION 3.1)

project(libjumanpp)

set(libjumanpp_VERSION_MAJOR 0)
set(libjumanpp_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT JPP_MAX_DIC_FIELDS)
    set(JPP_MAX_DIC_FIELDS 16)
endif ()

find_package(Threads)
find_library(pathie-shared NAMES libpathie.so PATHS /usr/lib /usr/local/lib)
find_library(execinfo-shared NAMES libexecinfo.so PATHS /usr/lib /usr/local/lib)

set(CMAKE_CXX_FLAGS "-fPIC")

set(JPP_DIR ${CMAKE_SOURCE_DIR}/jumanpp-2.0.0-rc3)

include(cmake/download.cmake)

add_subdirectory(jumanpp-2.0.0-rc3)

add_library(jumanpp-shared SHARED
    ${CMAKE_SOURCE_DIR}/src/jumanpp.cc
    ${CMAKE_SOURCE_DIR}/include/jumanpp/jumanpp.h)

add_dependencies(jumanpp-shared jpp_jumandic)

target_include_directories(jumanpp-shared PUBLIC
    ${JPP_DIR}/libs
    ${JPP_DIR}/src
    ${CMAKE_BINARY_DIR}/jumanpp-2.0.0-rc3/src/core/cfg)

target_include_directories(jumanpp-shared PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/jumanpp-2.0.0-rc3/src/jumandic/gen)

if (execinfo-shared)
    target_link_libraries(jumanpp-shared ${execinfo-shared})
endif ()

target_link_libraries(jumanpp-shared 
    ${pathie-shared} 
    ${CMAKE_THREAD_LIBS_INIT} 
    Threads::Threads
    jpp_util
    jpp_rnn
    jpp_core
    jpp_jumandic_spec
    jpp_jumandic)

set_target_properties(jumanpp-shared PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(jumanpp-shared PROPERTIES OUTPUT_NAME jumanpp)

install(FILES ${CMAKE_BINARY_DIR}/libjumanpp.so DESTINATION lib)
install(FILES ${CMAKE_SOURCE_DIR}/include/jumanpp/jumanpp.h DESTINATION include/jumanpp)
