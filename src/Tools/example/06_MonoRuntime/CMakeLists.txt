#cmake_minimum_required(VERSION 3.12)
set(Project_name "06_MonoRuntime")

project(${Project_name})

file(GLOB headers 
"include/*.h"
"include/*.h??"
)
file(GLOB sources 
"src/*.cpp"
)

include_directories("include")
include_directories("/usr/local/include/mono-2.0")

add_executable_beautiful(${Project_name} ${headers} ${sources})

set(libpath /usr/local/lib)
find_library (MONO libmono-2.0.a ${libpath})
target_link_libraries(${Project_name} ${MONO})
