# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CalculatorGui_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CalculatorGui_autogen.dir\\ParseCache.txt"
  "CalculatorGui_autogen"
  )
endif()
