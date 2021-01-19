
set(clog_src clog.c)
if(CLOG_HAVE_THREAD)
  list(APPEND clog_src threadingStrategy.c)
endif()

add_library(clog STATIC ${clog_src})
add_library(clog_shared SHARED ${clog_src})
set_target_properties(clog_shared PROPERTIES OUTPUT_NAME clog)

foreach(c clog clog_shared)
  target_include_directories(${c} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                         ${PROJECT_BINARY_DIR})
endforeach()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/clog_config.h.in
  ${PROJECT_BINARY_DIR}/clog_config.h)
