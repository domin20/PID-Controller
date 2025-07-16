cmake_minimum_required(VERSION 3.14)
project(PIDController LANGUAGES CXX)

file(GLOB PID_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(PIDController STATIC ${PID_SOURCES})

target_include_directories(PIDController
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(PIDController PRIVATE
    -Wall -Wextra -Wpedantic
)