cmake_minimum_required(VERSION 3.14)
project(pid-controller LANGUAGES CXX)

add_library(pid-controller STATIC
    src/PID.cpp
)

target_include_directories(pid-controller
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(pid-controller PUBLIC cxx_std_17)

target_compile_options(pid-controller PRIVATE
    -Wall -Wextra -Wpedantic
)