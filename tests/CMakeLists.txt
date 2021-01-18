
set(targets testLevels testFormat testCallbacks)

set(libraries clog)

if(CLOG_USE_PTHREAD)
  list(APPEND targets testPthread)
  list(APPEND libraries Threads::Threads)
endif()

foreach(target ${targets})
  add_executable(${target} "${target}.c")
  target_link_libraries(${target} PRIVATE ${libraries})
endforeach()
