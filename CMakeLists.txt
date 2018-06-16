cmake_minimum_required (VERSION 3.1)
project (Editor)                    #创建Editor 项目
project (TmingEngine)               #创建引擎核心逻辑库

set(CMAKE_CXX_STANDARD 11)          #使用c++ 11
aux_source_directory(src DIR_Main)  # 查找src目录下的所有源文件 并将名称保存到 DIR_Main 变量

add_subdirectory(src)               #添加一个子目录


add_executable(Editor ${sources})       #编辑器 添加源代码

target_link_libraries(TestLib)
