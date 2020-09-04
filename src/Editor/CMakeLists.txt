file(GLOB headers 
"*.h"
"UI/*.h??"
"UI/*.h"
"Utility/*.h"
"Utility/*.h??"
)

file(GLOB sources 
"*.cpp"
"Utility/*.cpp"
"UI/*.cpp"
)

include_directories("UI/WidgetBase")    #添加头文件目录
include_directories("../../include")    #添加头文件目录
include_directories("../../include/lua/src")    #添加头文件目录
include_directories("../../include/angelscript")    #添加头文件目录
include_directories("../Engine")        #添加头文件目录
include_directories("Utility")          #添加头文件目录
include_directories("UI")				#添加头文件目录
include_directories("../ThirdParty/Angelscript/sdk/add_on")
include_directories(${DEST_INCLUDE_DIR}/yaml-cpp/include)
include_directories(${DEST_INCLUDE_DIR}/gl3w)

if(WIN32)
include_directories("C:/Program Files/Mono/include/mono-2.0")
elseif(APPLE)
include_directories("/Library/Frameworks/Mono.framework/Versions/Current/include/mono-2.0")
endif()

add_executable_beautiful(Editor ${headers} ${sources})

set(libpath ${PROJECT_SOURCE_DIR}/Library/static)
target_link_libraries(Editor TmingEngine)

if(APPLE)                        #glfw3 需要一些mac 的原生库
target_link_libraries(Editor "-framework CoreFoundation")
target_link_libraries(Editor "-framework Cocoa")
target_link_libraries(Editor "-framework OpenGL")
target_link_libraries(Editor "-framework IOKit")
target_link_libraries(Editor "-framework CoreVideo")
elseif(WIN32)
target_link_libraries(Editor "opengl32.lib")
endif()

#add_custom_command(TARGET Editor POST_BUILD     #拷贝文件夹             
#COMMAND ${CMAKE_COMMAND} -E copy_directory                     
#"${PROJECT_SOURCE_DIR}/Library/shared"                                                     
#$<TARGET_FILE_DIR:Editor>)



