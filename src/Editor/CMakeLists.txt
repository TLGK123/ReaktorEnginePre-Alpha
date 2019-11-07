file(GLOB headers 
"*.h"
"UI/WidgetBase/*.h"
"UI/WidgetBase/*.h??"
"UI/*.h??"
"UI/*.h"
"Core/*.h"
"Core/*.h??"
)

file(GLOB sources 
"*.cpp"
"Core/*.cpp"
"UI/WidgetBase/*.cpp"
"UI/*.cpp"
)

include_directories("UI/WidgetBase")    #添加头文件目录
include_directories("../../include")    #添加头文件目录
include_directories("../Engine")        #添加头文件目录
include_directories("Core")             #添加头文件目录
include_directories("UI")				#添加头文件目录

add_executable_beautiful(Editor ${headers} ${sources})

set(libpath ${PROJECT_SOURCE_DIR}/Library/static)
target_link_libraries(Editor TmingEngine)

if(APPLE)                        #glfw3 需要一些mac 的原生库
target_link_libraries(Editor "-framework CoreFoundation")
target_link_libraries(Editor "-framework Cocoa")
target_link_libraries(Editor "-framework OpenGL")
target_link_libraries(Editor "-framework IOKit")
target_link_libraries(Editor "-framework CoreVideo")
endif(APPLE)

if(WIN32)
set(monoPath ${PROJECT_SOURCE_DIR}/Data/mono)
link_directories(${monoPath}/bin) #必须在添加 target 前进行设置
set(libpath ${monoPath}/lib)
find_library (mono mono-2.0-sgen.lib ${libpath})
set_property(TARGET Editor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${monoPath}/bin)
target_link_libraries(Editor ${mono})
endif()

#add_custom_command(TARGET Editor POST_BUILD     #拷贝文件夹             
#COMMAND ${CMAKE_COMMAND} -E copy_directory                     
#"${PROJECT_SOURCE_DIR}/Library/shared"                                                     
#$<TARGET_FILE_DIR:Editor>)

ADD_DEFINITIONS(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

