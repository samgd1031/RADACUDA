cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Werror)

project(RADACUDA)

add_subdirectory(src)
add_executable(radacuda src/main.cpp)
target_link_libraries(radacuda radacuda_src)