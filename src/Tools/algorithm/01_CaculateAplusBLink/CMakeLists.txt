#cmake_minimum_required(VERSION 3.12)
set(Project_Name 01_CaculateAplusBLink)
project(${Project_Name})

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")

add_executable(${Project_Name}  ${headers} ${sources})
