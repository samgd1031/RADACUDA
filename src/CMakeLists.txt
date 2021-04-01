cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADER_FILES CONFIGURE_DEPENDS "*.h")
file(GLOB SRC_FILES CONFIGURE_DEPENDS "*.cc")

add_library(radacuda_src STATIC ${SRC_FILES} ${HEADER_FILES})

target_include_directories(radacuda_src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(radacuda_src PUBLIC cxx_std_20)

target_compile_options(radacuda_src PUBLIC -Wall -Werror)
