cmake_minimum_required(VERSION 3.8)

#add_executable(module01Test module01_test.cpp)
add_executable(schedulerTest scheduler_test.cpp)

#target_link_libraries(module01Test PUBLIC gtest_main Project01)
target_link_libraries(schedulerTest PUBLIC gtest_main gmock_main Project01)

#<add_test(
#  NAME module01Test,
#  COMMAND module01Test)

add_test(
  NAME schedulerTest,
  COMMAND schedulerTest)  