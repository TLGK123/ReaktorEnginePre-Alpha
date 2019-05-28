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
include_directories(${DEST_INCLUDE_DIR})

add_executable_beautiful(${Project_name} ${headers} ${sources})


set(libpath /Library/Frameworks/Mono.framework/Versions/Current/lib)
#set(libpath ${DEST_LIB_DIR}/shared)   #无法直接抽离出一个库文件。它和很多文件相关

#message(${libpath})

find_library (mono libmono-2.0.dylib ${libpath})
target_link_libraries(${Project_name} ${mono})

#add_custom_command(TARGET ${Project_name} POST_BUILD        #拷贝文件夹
#COMMAND ${CMAKE_COMMAND} -E copy_directory
#"${libpath}"                                                #需要被拷贝的共享dll文件夹
#$<TARGET_FILE_DIR:${Project_name}>)
