cmake_minimum_required(VERSION 3.10)
project(radacuda_src)

file(GLOB src_files "*.cpp")

add_library(radacuda_src STATIC ${src_files})

target_include_directories(radacuda_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})