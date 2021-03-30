cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
project(radacuda_src)

file(GLOB src_files "*.cc")

add_library(radacuda_src STATIC ${src_files})

target_include_directories(radacuda_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})