cmake_minimum_required (VERSION 3.1)

project(clog C)

option(CLOG_USE_PTHREAD "" ON)

if(CLOG_USE_PTHREAD)
  find_package(Threads REQUIRED)
endif()

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME TestLogLevels COMMAND $<TARGET_FILE:testLevels>)
add_test(NAME TestLogFormat COMMAND $<TARGET_FILE:testFormat>)
add_test(NAME TestLogCallbacks COMMAND $<TARGET_FILE:testCallbacks>)

install(TARGETS testLevels testFormat testCallbacks DESTINATION bin)
if(CLOG_USE_PTHREAD)
  add_test(NAME TestPthread COMMAND $<TARGET_FILE:testPthread>)
  install(TARGETS testPthread DESTINATION bin)
endif()

install(TARGETS clog_shared clog DESTINATION lib)
install(FILES src/lib/clog.h DESTINATION include)
