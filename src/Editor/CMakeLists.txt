file(GLOB headers 
"*.h"
"UI/Widgets/Widget.h"
"../../include/im.h"
"Demo/*.h"
"../../include/stb_image.h"
)

file(GLOB sources 
"*.cpp"
"Core/*.cpp"
"Demo/*.cpp"
"imgui/*.cpp"
"Model/*.cpp"
"UI/Widgets/Widget.cpp"
"UI/Widgets/Console.cpp"
"UI/Widgets/DemoMenu.cpp" 
"../Engine/3Part/Box2D/Testbed/Framework/DebugDraw.cpp"
"../Engine/Model/model.cpp"
"../../include/*.cpp"
)

include_directories("UI/Widgets")    #添加头文件目录
include_directories("../../include")    #添加头文件目录
include_directories("../Engine")    #添加头文件目录
include_directories("../Engine/3Part/Box2D")    #添加头文件目录
include_directories("../Engine/3Part/Box2D/Testbed/Framework")    #添加头文件目录
include_directories("Demo")    #添加头文件目录
include_directories("Core")    #添加头文件目录

add_executable(Editor ${headers} ${sources})

set(libpath ${PROJECT_SOURCE_DIR}/lib)

if(WIN32)
find_library (GLFW glfw3.lib ${libpath})
find_library(ASSIMP assimp-vc140-mt.lib ${libpath})
add_custom_command(TARGET Editor POST_BUILD        # Adds a post-build event to Editor
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/lib/assimp-vc140-mt.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:Editor>)                 # <--this is out-file path

elseif(APPLE)
find_library (GLFW libglfw3.a ${libpath}) 
find_library(ASSIMP libassimp.4.1.0.dylib ${libpath})
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
