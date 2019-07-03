set(ProjectName "TextEditor")
project (${ProjectName})
file (GLOB heads *.h)
file( GLOB sources *.cpp *.c)
include_directories("../../../include")

add_library_beautiful(${ProjectName} ${heads} ${sources})

install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/${ProjectName} FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
