# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\optical_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\optical_autogen.dir\\ParseCache.txt"
  "optical_autogen"
  )
endif()
