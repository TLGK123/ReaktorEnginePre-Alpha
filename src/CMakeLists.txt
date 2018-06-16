
file(GLOB headers "*.h")
file(GLOB sources "*.cpp")

if (true)
    list(APPEND sources ${headers})
endif()

add_library(TestLib STATIC ${sources}) #生成一个 TestLib 静态库

if (UNIX)
    target_link_libraries(TestLib core ) 
endif()
