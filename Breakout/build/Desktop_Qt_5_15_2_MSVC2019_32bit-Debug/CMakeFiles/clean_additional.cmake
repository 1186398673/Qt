# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Breakout_autogen"
  "CMakeFiles\\Breakout_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Breakout_autogen.dir\\ParseCache.txt"
  )
endif()
