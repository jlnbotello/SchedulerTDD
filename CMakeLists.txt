cmake_minimum_required(VERSION 3.8)

set(PROJ_NAME Project01)

project(${PROJ_NAME} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SRC_DIR src)
set(INC_DIR inc)
set(SRC ${SRC_DIR}/module01.cpp)
set(INC ${INC_DIR}/module01.hpp)

include_directories(${INC_DIR})
add_library(${PROJ_NAME} STATIC ${SRC} ${INC})

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)