# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GEmploye_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GEmploye_autogen.dir\\ParseCache.txt"
  "GEmploye_autogen"
  )
endif()
