#cmake_minimum_required(VERSION 3.12)
set(Project_Name 01_CaculateAplusB)
project(01_CaculateAplusB)

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")

add_executable(${Project_Name}  ${headers} ${sources})
