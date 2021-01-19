cmake_minimum_required(VERSION 3.1)

project(clog C)

include(CMakeDependentOption)

option(CLOG_USE_THREAD "Use threads for logging barriers" OFF)
if(CLOG_USE_THREAD)
  set(CLOG_HAVE_THREAD 1)
endif()
cmake_dependent_option(CLOG_USE_PTHREAD "Use Pthread intrinsics for logging barriers" ON
  "CLOG_USE_THREAD" OFF)
cmake_dependent_option(CLOG_USE_MPI "Use MPI for logging barriers" OFF
  "CLOG_USE_THREAD" OFF)

add_library(clog_libraries INTERFACE)

if(CLOG_USE_PTHREAD)
  find_package(Threads REQUIRED)
  set(CLOG_HAVE_PTHREAD 1)
  target_link_libraries(clog_libraries INTERFACE Threads::Threads)
endif()

if(CLOG_USE_MPI)
  find_package(MPI REQUIRED)
  set(CLOG_HAVE_MPI 1)
  target_link_libraries(clog_libraries INTERFACE MPI::MPI_C)
endif()

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME TestLogLevels COMMAND $<TARGET_FILE:testLevels>)
add_test(NAME TestLogFormat COMMAND $<TARGET_FILE:testFormat>)
add_test(NAME TestLogCallbacks COMMAND $<TARGET_FILE:testCallbacks>)

install(TARGETS testLevels testFormat testCallbacks DESTINATION bin)
if(CLOG_HAVE_THREAD)
  if(CLOG_HAVE_PTHREAD)
    add_test(NAME TestPthread COMMAND $<TARGET_FILE:testPthread>)
    install(TARGETS testPthread DESTINATION bin)
  endif()
endif()

install(TARGETS clog_shared clog DESTINATION lib)
install(FILES src/lib/clog.h DESTINATION include)
