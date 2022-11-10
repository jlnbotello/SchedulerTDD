cmake_minimum_required(VERSION 3.8)

set(PROJ_NAME Project01Test)

set(SRC module01_test.cpp)

add_executable(${PROJ_NAME} ${SRC})

target_link_libraries(${PROJ_NAME} PUBLIC gtest_main Project01)

add_test(
  NAME ${PROJ_NAME}
  COMMAND ${PROJ_NAME})