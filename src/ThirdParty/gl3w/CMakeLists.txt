set(ProjectName "gl3w")
project (${ProjectName})
file (GLOB heads GL/*.h)
file( GLOB sources GL/*.cpp GL/*.c)
include_directories(".")
include_directories("../")

add_library_beautiful(${ProjectName} STATIC ${heads} ${sources})

install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/${ProjectName} FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
