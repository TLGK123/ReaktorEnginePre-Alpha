
file(GLOB headers "*.h")
file(GLOB sources "*.cpp")

if (true)
    list(APPEND sources ${headers})
endif()

add_library(client STATIC ${sources})

if (UNIX)
    target_link_libraries(client core io)
endif()
