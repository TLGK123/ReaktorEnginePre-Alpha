file(GLOB headers "*.h")
file(GLOB sources "*.cpp" "*.c")
include_directories("../../include")    #添加头文件目录
if (SYNERGY_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_executable(Editor ${sources})

set(libpath ${PROJECT_SOURCE_DIR}/lib)

if(WIN32)
find_library (GLFW glfw3.lib ${libpath})
else()
find_library (GLFW glfw3.a ${libpath})   
endif()

message(${GLFW})
target_link_libraries(Editor ${GLFW})

if(APPLE)
message("Link Mac OS framework")                            #glfw3 需要一些mac 的原生库
target_link_libraries(Editor "-framework CoreFoundation")
target_link_libraries(Editor "-framework Cocoa")
target_link_libraries(Editor "-framework OpenGL")
target_link_libraries(Editor "-framework IOKit")
target_link_libraries(Editor "-framework CoreVideo")

endif(APPLE)
