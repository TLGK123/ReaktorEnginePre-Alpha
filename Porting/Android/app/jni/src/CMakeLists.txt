

find_library(SDL2 SDL2)

add_library(main SHARED main.c)

target_link_libraries(main SDL2)


