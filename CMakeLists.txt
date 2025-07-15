cmake_minimum_required(VERSION 3.14)
project(pid-controller LANGUAGES CXX)

file(GLOB PID_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(pid-controller STATIC ${PID_SOURCES})

target_include_directories(pid-controller
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(pid-controller PRIVATE
    -Wall -Wextra -Wpedantic
)