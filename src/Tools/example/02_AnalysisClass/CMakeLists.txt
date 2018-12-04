#cmake_minimum_required(VERSION 3.12)
set(Project_name "02_AnalysisClass")

project(${Project_name})

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")
include_directories("../../FileFilter/include")
include_directories("../../FileReader/include")

add_executable(${Project_name}  ${headers} ${sources})
target_link_libraries(${Project_name} FileFilter)
target_link_libraries(${Project_name} FileReader)