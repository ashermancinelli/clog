set(targets testLevels testFormat testCallbacks)

set(libraries clog)

if(CLOG_HAVE_THREAD)
  if(CLOG_HAVE_PTHREAD)
    list(APPEND targets testPthread)
    list(APPEND libraries Threads::Threads)
  endif()
endif()

foreach(target ${targets})
  add_executable(${target} "${target}.c")
  target_link_libraries(${target} PRIVATE ${libraries})
endforeach()
