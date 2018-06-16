cmake_minimum_required (VERSION 3.1)
project (Editor)                    #创建Editor 项目
project (TmingEngine)               #创建引擎核心逻辑库

set(CMAKE_CXX_STANDARD 11)          #使用c++ 11

set(SYNERGY_ADD_HEADERS true)

add_subdirectory(src)               #添加一个子目录

