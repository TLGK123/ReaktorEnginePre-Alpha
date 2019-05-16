#cmake_minimum_required(VERSION 3.12)
set(Project_name "03_OperateExcel")

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
include_directories("../../xlnt-master/include")

add_executable(${Project_name}  ${headers} ${sources})

#target_link_libraries(${Project_name} FileFilter)
#target_link_libraries(${Project_name} FileReader)
target_link_libraries(${Project_name} xlnt)
