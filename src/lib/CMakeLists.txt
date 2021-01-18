add_library(clog STATIC clog.c)
add_library(clog_shared SHARED clog.c)
set_target_properties(clog_shared
  PROPERTIES OUTPUT_NAME clog)

foreach(c clog clog_shared)
  target_include_directories(${c} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR})

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/clog_config.h.in
    ${PROJECT_BINARY_DIR}/clog_config.h)

  target_link_libraries(clog PRIVATE Threads::Threads)
endforeach()
