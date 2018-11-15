#cmake_minimum_required(VERSION 3.12)
project(01_CaculateCode)

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

add_executable(01_CaculateCode  ${headers} ${sources})
target_link_libraries(01_CaculateCode FileFilter)
target_link_libraries(01_CaculateCode FileReader)