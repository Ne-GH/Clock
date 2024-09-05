# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Clock_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Clock_autogen.dir/ParseCache.txt"
  "CMakeFiles/Module_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Module_autogen.dir/ParseCache.txt"
  "Clock_autogen"
  "Module_autogen"
  )
endif()
