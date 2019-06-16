#cmake_minimum_required(VERSION 3.12)
set(Project_name "09_ChezTest")

project(${Project_name})

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")
set(DEST_LIB_DIR ./Library)
add_library(${Project_name} SHARED ${headers} ${sources})
