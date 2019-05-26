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
include_directories("UI")             #添加头文件目录

add_executable_beautiful(Editor ${headers} ${sources})

set(libpath ${PROJECT_SOURCE_DIR}/Library/static)

if(WIN32)
find_library (GLFW glfw3.lib ${libpath})
find_library (ASSIMP assimp-vc140-mt.lib ${libpath})
elseif(APPLE)
find_library (GLFW libglfw3.a ${libpath}) 
find_library (ASSIMP libassimp.4.1.0.dylib ${libpath})
endif()


target_link_libraries(Editor ${GLFW})
target_link_libraries(Editor TmingEngine)
target_link_libraries(Editor ${ASSIMP})

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

if(WIN32)
message(${ASSIMP})
CopyFile(Editor ${ASSIMP})                                              
endif()

ADD_DEFINITIONS(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

