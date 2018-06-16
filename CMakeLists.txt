cmake_minimum_required (VERSION 3.1)
project (Editor)                    #创建Editor 项目
project (TmingEngine)               #创建引擎核心逻辑库

set(CMAKE_CXX_STANDARD 11)          #使用c++ 11
aux_source_directory(src DIR_Main)  # 查找src目录下的所有源文件 并将名称保存到 DIR_Main 变量

#添加一个子目录
add_subdirectory(src)

include_directories("${PROJECT_SOURCE_DIR}/include")



#IDE中分文件夹
source_group("FileSystem" FILES ${DIR_FileSystem})
source_group("ImGui" FILES ${DIR_Imgui})
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
source_group("UI" FILES ${DIR_UI})

add_executable(Editor ${DIR_Main} ${DIR_UI}
${DIR_Imgui})
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
if()
   target_link_libraries(TmingEngine ${GLFW}) 
endif()

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
if(WIN32)
    message("windows platform ")
    target_link_libraries(TmingEngine ${PROJECT_SOURCE_DIR}/lib/glfw3.lib)
elseif(APPLE)
    message("Apple platform ")
    target_link_libraries(TmingEngine ${PROJECT_SOURCE_DIR}/lib/glfw3.a)
elseif(UNIX)
    message("UNIX platform ")
endif()
 
target_link_libraries(TmingEngine ${PROJECT_SOURCE_DIR}/lib/assimp-vc140-mt.lib)
target_link_libraries(Editor TmingEngine)
#target_link_libraries(Editor -lassimp-vc140-mt.dll)
