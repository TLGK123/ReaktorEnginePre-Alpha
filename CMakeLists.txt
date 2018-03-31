cmake_minimum_required (VERSION 3.1)
project (Editor)
project (TmingEngine)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
set(CMAKE_CXX_STANDARD 17) #使用c++ 17
aux_source_directory(src DIR_Main)
aux_source_directory(src/FileSystem DIR_FileSystem)
aux_source_directory(src/Imgui DIR_Imgui)
aux_source_directory(src/Core DIR_Core)
aux_source_directory(src/OpenGL DIR_OpenGL)
aux_source_directory(src/Plantform DIR_Plantform)
aux_source_directory(src/Math DIR_Math)
aux_source_directory(src/Logging DIR_Log)
aux_source_directory(src/Scene DIR_Scene)
aux_source_directory(src/Threading DIR_Threading)
aux_source_directory(src/Scene/Components DIR_Components)
aux_source_directory(src/IO DIR_IO)
aux_source_directory(src/Graphics DIR_Graphics)
aux_source_directory(src/Resource DIR_Resource)

#aux_source_directory(src/Math DIR_SRCS5)
#add_subdirectory(src/Core)
#add_subdirectory(world)
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_target_properties(${TmingEngine} PROPERTIES FOLDER GUI/Dialogs)

#function(group_by_dir src_dir)
#foreach(FILE ${ARGN})
# 获取文件绝对路径
#get_filename_component(FULL_NAME "${FILE}" ABSOLUTE)

# 获取文件父路径
#get_filename_component(PARENT_DIR "${FULL_NAME}" PATH)

# 移除父路径中的源码根路径
#string(REPLACE "${ARGV0}" "" GROUP "${PARENT_DIR}")

# 确保路径使用windows路径符号
#string(REPLACE "/" "\\" GROUP "${GROUP}")
# 将文件归组到 "Source Files" 和 "Header Files"

#if("${FILE}" MATCHES ".*\\.h")
#set(GROUP "Header Files${GROUP}")
#else()
#set(GROUP "Source Files${GROUP}")
#endif()
#message(${GROUP})
#source_group("${GROUP}" FILES "${FILE}")
#endforeach()
#endfunction(group_by_dir)

#group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${INC_LIST})
#group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} ${SRC_LIST})

 # 指定生成目标
include_directories("${PROJECT_SOURCE_DIR}/include")
#link_libraries("lib/glfw3.lib")
#find_library(glfw3.lib ${PROJECT_SOURCE_DIR}/lib)
#link_directories("${PROJECT_SOURCE_DIR}/lib")
#IDE中分文件夹
source_group("FileSystem" FILES ${DIR_FileSystem})
source_group("Imgui" FILES ${DIR_Imgui})
source_group("Core" FILES ${DIR_Core})
source_group("Plantform" FILES ${DIR_Plantform})
source_group("OpenGL" FILES ${DIR_OpenGL})
source_group("Math" FILES ${DIR_Math})
source_group("Logging" FILES ${DIR_Log})
source_group("Scene" FILES ${DIR_Scene})
source_group("Threading" FILES ${DIR_Threading})
source_group("Scene\\Components" FILES ${DIR_Components})
source_group("IO" FILES ${DIR_IO})
source_group("Graphics" FILES ${DIR_Graphics})
source_group("Resource" FILES ${DIR_Resource})

add_executable(Editor ${DIR_Main} ${DIR_Imgui})
add_library(TmingEngine STATIC
 ${DIR_FileSystem} ${DIR_OpenGL} ${DIR_Log} ${DIR_Scene} ${DIR_Resource}
 ${DIR_Threading} ${DIR_Components} ${DIR_IO} ${DIR_Graphics}
 ${DIR_Core} ${DIR_Plantform} ${DIR_Math})

#寻找lib文件
# PROJECT_SOURCE_DIR 工程的根目录
# CMAKE_CURRENT_SOURCE_DIR
set(libpath ${PROJECT_SOURCE_DIR}/lib)
message(${libpath})
find_library (GLFW glfw3.lib ${libpath})
message(${GLFW})
if(FoundLIB)
   target_link_libraries(TmingEngine ${GLFW}) 
endif()

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(TmingEngine ${PROJECT_SOURCE_DIR}/lib/glfw3.lib)
target_link_libraries(TmingEngine ${PROJECT_SOURCE_DIR}/lib/assimp-vc140-mt.lib)
target_link_libraries(Editor TmingEngine)
#target_link_libraries(Editor -lassimp-vc140-mt.dll)
