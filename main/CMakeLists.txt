cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

add_executable(radacuda main.cpp)

target_link_libraries(radacuda radacuda_src)
target_compile_features(radacuda PUBLIC cxx_std_20)
target_compile_options(radacuda PUBLIC -Wall -Werror)
