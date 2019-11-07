


include_directories("../../../include")    #添加头文件目录
include_directories("../../../include/ImGui")    #添加头文件目录
include_directories("Include")    
add_library_beautiful(imgui_canvas STATIC
    Source/imgui_canvas.cpp
    Source/imgui_canvas.h
)


set(_imgui_node_editor_Sources
    Include/imgui_node_editor.h
    Source/crude_json.cpp
    Source/crude_json.h
    Source/imgui_bezier_math.h
    Source/imgui_bezier_math.inl
    Source/imgui_canvas.cpp
    Source/imgui_canvas.h
    Source/imgui_extra_math.h
    Source/imgui_extra_math.inl
    Source/imgui_node_editor_api.cpp
    Source/imgui_node_editor_internal.h
    Source/imgui_node_editor_internal.inl
    Source/imgui_node_editor.cpp
    Support/imgui_node_editor.natvis
)

add_library_beautiful(imgui_node_editor STATIC ${_imgui_node_editor_Sources})
