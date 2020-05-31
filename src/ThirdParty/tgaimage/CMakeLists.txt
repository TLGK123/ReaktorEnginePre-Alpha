project (tgaimage)
file (GLOB heads *.h)
file( GLOB sources *.cpp)
include_directories("include")

add_library_beautiful(tgaimage STATIC ${heads} ${sources})

install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/tgaimage FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
