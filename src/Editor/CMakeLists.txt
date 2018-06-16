file(GLOB headers "*.h")
file(GLOB sources "*.cpp")

if (SYNERGY_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_executable(Editor STATIC ${sources})