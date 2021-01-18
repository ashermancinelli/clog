 add_library(clog clog.c)
target_include_directories(clog PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/clog_config.h.in
  ${PROJECT_BINARY_DIR}/clog_config.h)
