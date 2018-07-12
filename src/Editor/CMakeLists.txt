file(GLOB headers "*.h" "UI/Widgets/Widget.h")
file(GLOB sources "*.cpp" "*.c" "UI/Widgets/Widget.cpp")
include_directories("../../include")    #添加头文件目录
include_directories("../Engine")    #添加头文件目录
aux_source_directory(opengl DIR_Main)

list(APPEND sources ${headers} ${DIR_Main})

add_executable(Editor ${sources}) 

set(libpath ${PROJECT_SOURCE_DIR}/lib)

if(WIN32)
find_library (GLFW glfw3.lib ${libpath})
else()
find_library (GLFW libglfw3.a ${libpath}) 
endif()

message(${DIR_Main})
target_link_libraries(Editor ${GLFW})
target_link_libraries(Editor TmingEngine)
if(APPLE)
message("Link Mac OS framework")                            #glfw3 需要一些mac 的原生库
target_link_libraries(Editor "-framework CoreFoundation")
target_link_libraries(Editor "-framework Cocoa")
target_link_libraries(Editor "-framework OpenGL")
target_link_libraries(Editor "-framework IOKit")
target_link_libraries(Editor "-framework CoreVideo")

endif(APPLE)
