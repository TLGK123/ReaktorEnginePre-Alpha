#cmake_minimum_required(VERSION 3.12)
project(FileReader)

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")
add_library(FileReader  ${headers} ${sources})