cmake_minimum_required (VERSION 3.1)
project (Editor)                    #创建Editor 项目
project (TmingEngine)               #创建引擎核心逻辑库

macro(CopyFile projectName fileFullPath)                                            #拷贝动态库到程序运行目录 的宏处理
add_custom_command(TARGET ${projectName} POST_BUILD                
COMMAND ${CMAKE_COMMAND} -E copy_if_different                  
"${fileFullPath}"                                                      
$<TARGET_FILE_DIR:${projectName}>)
endmacro()


set(CMAKE_CXX_STANDARD 11)          #使用c++ 11

set(SYNERGY_ADD_HEADERS true)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/tm)

add_subdirectory(src)               #添加一个子目录

