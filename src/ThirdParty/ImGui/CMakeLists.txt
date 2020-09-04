project (ImGui)
file (GLOB heads *.h)
file( GLOB sources *.cpp)
include_directories("../../../include")
include_directories("../../../include/SDL/include")
include_directories(${DEST_INCLUDE_DIR}/gl3w)

add_library_beautiful(ImGui STATIC ${heads} ${sources})

add_definitions(-DCOMPILING_LIB)






install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ImGui FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
