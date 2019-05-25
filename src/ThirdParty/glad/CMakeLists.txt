
message("------check----------")
message(${DEST_INCLUDE_DIR})
install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR} FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 