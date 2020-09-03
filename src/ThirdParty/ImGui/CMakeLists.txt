project (ImGui)
file (GLOB heads *.h)
file( GLOB sources *.cpp)
include_directories("../../../include")
include_directories("../../../include/SDL/include")
include_directories(${DEST_INCLUDE_DIR}/gl3w)

add_library_beautiful(ImGui STATIC ${heads} ${sources})

add_definitions(-DCOMPILING_LIB)



if(WIN32)
    message("Windows imgui ±‡“Î…Ë÷√ IMGUI_IMPL_OPENGL_LOADER_GL3W")
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W)
elseif(IOS)
    message("iOS imgui ±‡“Î…Ë÷√ IMGUI_IMPL_OPENGL_ES3")
    add_definitions(-DIMGUI_IMPL_OPENGL_ES3)
elseif(APPLE)
    message("Mac OS imgui ±‡“Î…Ë÷√ IMGUI_IMPL_OPENGL_LOADER_GL3W")
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W)
elseif(ANDROID)
    message("Android imgui ±‡“Î…Ë÷√ IMGUI_IMPL_OPENGL_ES3")
    add_definitions(-DIMGUI_IMPL_OPENGL_ES3)
elseif(LINUX)
    message("Linux  ±‡“Î…Ë÷√ IMGUI_IMPL_OPENGL_ES3")
    add_definitions(-DIMGUI_IMPL_OPENGL_ES3)
endif()


install_header_files (DIRECTORY ./ DESTINATION ${DEST_INCLUDE_DIR}/ImGui FILES_MATCHING PATTERN *.hpp *.h USE_FILE_SYMLINK BUILD_TREE_ONLY) 
