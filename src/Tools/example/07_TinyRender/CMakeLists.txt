#cmake_minimum_required(VERSION 3.12)
set(Project_name "07_TinyRender")

project(${Project_name})

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")

add_executable(${Project_name}  ${headers} ${sources})
