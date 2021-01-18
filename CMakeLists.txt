cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(clog C)

option(CLOG_USE_PTHREAD "" ON)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME TestLogLevels COMMAND $<TARGET_FILE:testLevels>)
add_test(NAME TestLogFormat COMMAND $<TARGET_FILE:testFormat>)
