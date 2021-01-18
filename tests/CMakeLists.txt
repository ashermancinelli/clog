add_executable(testLevels testLevels.c)
add_executable(testFormat testFormat.c)

foreach(tgt testLevels testFormat)
  target_link_libraries(${tgt} PRIVATE clog)
endforeach()
