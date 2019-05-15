cmake_minimum_required (VERSION 3.1)
project (Editor)                    #创建Editor 项目
project (TmingEngine)               #创建引擎核心逻辑库

macro(CopyFile projectName fileFullPath)                                            #拷贝动态库到程序运行目录 的宏处理
add_custom_command(TARGET ${projectName} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${fileFullPath}"
$<TARGET_FILE_DIR:${projectName}>)
endmacro()

function(assign_source_group)
foreach(_source IN ITEMS ${ARGN})
if (IS_ABSOLUTE "${_source}")
file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
else()
set(_source_rel "${_source}")
endif()
get_filename_component(_source_path "${_source_rel}" PATH)
string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()
endfunction(assign_source_group)

function(add_executable_beautiful)
foreach(_source IN ITEMS ${ARGN})
assign_source_group(${_source})
endforeach()
add_executable(${ARGV})
endfunction(add_executable_beautiful)

function(add_library_beautiful)
foreach(_source IN ITEMS ${ARGN})
assign_source_group(${_source})
endforeach()
add_library(${ARGV})
endfunction(add_library_beautiful)


set(CMAKE_CXX_STANDARD 17)          #使用c++ 11

set(SYNERGY_ADD_HEADERS true)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/tm)

add_subdirectory(src)               #添加一个子目录

