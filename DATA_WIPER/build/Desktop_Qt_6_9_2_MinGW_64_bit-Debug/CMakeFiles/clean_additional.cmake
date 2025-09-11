# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DATA_WIPER_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DATA_WIPER_autogen.dir\\ParseCache.txt"
  "DATA_WIPER_autogen"
  )
endif()
