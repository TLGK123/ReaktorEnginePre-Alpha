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

if(WIN32)
include_directories("../../../ThirdParty")

elseif(APPLE)
include_directories("include")
endif()

include_directories(${DEST_INCLUDE_DIR})

if(WIN32)
link_directories("C:/Program Files/Mono/lib")   #必须再添加 target 前进行设置
link_directories("C:/Program Files/Mono/bin")
endif()

add_executable_beautiful(${Project_name} ${headers} ${sources})

if(APPLE)

set(libpath /Library/Frameworks/Mono.framework/Versions/Current/lib)
find_library (mono libmono-2.0.dylib ${libpath})
target_link_libraries(${Project_name} ${mono})

elseif(WIN32)

set(libpath "C:/Program Files/Mono/lib")

find_library (mono1 mono-2.0-sgen.lib ${libpath})
#find_library (mono2 mono-2.0-sgen.dll ${libpath2})
#message(${mono2})
target_link_libraries(${Project_name} ${mono1})
#target_link_libraries(${Project_name} ${mono2})
#target_link_directories(${Project_name} <PUBLIC>"C:/Program Files/Mono/bin")
endif()

if(WIN32)
#CopyFile(${Project_name} ${mono2})
#add_custom_command(TARGET ${Project_name} POST_BUILD     #拷贝文件夹             
#COMMAND ${CMAKE_COMMAND} -E copy_directory                     
#"C:/Program Files/Mono"                                                     
#$<TARGET_FILE_DIR:${Project_name}>)

endif()

if(WIN32)
#set( ENV{PATH} ../../../../Data/Tool )
elseif(APPLE)

endif()

message("12312312312")
execute_process(COMMAND touch aaa.jpg)
execute_process(COMMAND premake5 vs2019)
message("-----")
