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
include_directories("../../include/lua/src")    #添加头文件目录
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

add_custom_command(TARGET Editor POST_BUILD     #拷贝文件夹             
COMMAND ${CMAKE_COMMAND} -E copy_directory                     
"${PROJECT_SOURCE_DIR}/Library/shared"                                                     
$<TARGET_FILE_DIR:Editor>)

ADD_DEFINITIONS(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

