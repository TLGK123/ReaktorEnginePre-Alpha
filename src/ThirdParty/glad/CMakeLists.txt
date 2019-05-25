
message("------check----------")
message(${DEST_INCLUDE_DIR})

set (INCLUDE_DIRS .)

install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/glad FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 