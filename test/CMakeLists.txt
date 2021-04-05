cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
project(radacuda_test)

find_package(GTest REQUIRED)

file(GLOB test_files CONFIGURE_DEPENDS "*.cc")

add_executable(radacuda_test ${test_files})
target_link_libraries(radacuda_test GTest::GTest GTest::Main radacuda_src)
target_compile_features(radacuda_test PUBLIC cxx_std_20)
target_compile_options(radacuda_test PUBLIC -Wall -Werror)

gtest_discover_tests(radacuda_test)