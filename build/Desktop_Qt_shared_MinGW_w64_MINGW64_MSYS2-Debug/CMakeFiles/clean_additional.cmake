# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\pr_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\pr_autogen.dir\\ParseCache.txt"
  "pr_autogen"
  )
endif()
