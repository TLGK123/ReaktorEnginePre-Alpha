project (ImGui)
file (GLOB heads *.h)
file( GLOB sources *.cpp)
include_directories("../../../include")

add_library_beautiful(ImGui ${heads} ${sources})

add_definitions(-DCOMPILING_LIB)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ImGui FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
