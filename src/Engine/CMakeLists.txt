file(GLOB_RECURSE headers 
"Core/*.h"
"Core/*.h??"
"Core/Math/Vector2.h"
"Core/Math/Vector3.h"
"Core/Math/Matrix.h"
"Core/Math/Radian.h"
"Core/Math/Quaternion.h"

"Plantform/File/*.h"
"Plantform/File/*.hpp"
"Plantform/Time/*.h"
"Plantform/Windows/win/*.h"
"Plantform/Windows/*.h"
"Plantform/RHI/*.hpp"
"Plantform/RHI/*.h"

"Rendering/*.h"
"Rendering/*.h??"
"Rendering/RHI/*.hpp"

"SceneManager/*.h??"
"SceneManager/Components/Transform.h"
"SceneManager/Components/IComponent.h"

)

file(GLOB_RECURSE sources 
"Core/*.cpp" 
"Core/Math/Vector2.cpp"
"Core/Math/Vector3.cpp"
"Core/Math/Matrix.cpp"
"Core/Math/Quaternion.cpp"

"Plantform/File/*.cpp" 
"Plantform/Windows/win/*.cpp"
"Plantform/Windows/*.cpp"
"Plantform/RHI/*.cpp"

"Rendering/*.c"
"Rendering/*.c??"
"Plantform/Time/*.c??"

"SceneManager/*.cpp"
"SceneManager/Components/Transform.cpp"
"SceneManager/Components/IComponent.cpp"

) 

include_directories(${DEST_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})								
include_directories("../ThirdParty/Box2D/Testbed/Framework")            
include_directories("../ThirdParty/Angelscript/sdk/add_on")
include_directories("${DEST_INCLUDE_DIR}/include/angelscript")
include_directories(${DEST_INCLUDE_DIR}/ImGui)
include_directories(${DEST_INCLUDE_DIR}/yaml-cpp/include)
include_directories(${DEST_INCLUDE_DIR}/gl3w)
include_directories(${DEST_INCLUDE_DIR}/SDL/include)


set(libpath ${PROJECT_SOURCE_DIR}/Library/static)
link_directories(${libpath})

add_library_beautiful(TmingEngine STATIC ${headers} ${sources})

if(WIN32)
find_library (GLFW glfw3.lib ${libpath})
find_library (Mono mono-2.0-sgen.lib "C:/Program Files/Mono/lib")
elseif(APPLE)
find_library (GLFW libglfw3.a ${libpath})
find_library (Mono libmonosgen-2.0.a "/Library/Frameworks/Mono.framework/Versions/Current/lib")
elseif(UNIX)

endif()

target_link_libraries(TmingEngine lua)
target_link_libraries(TmingEngine Box2D)
target_link_libraries(TmingEngine SDL2main)
target_link_libraries(TmingEngine SDL2-static)
target_link_libraries(TmingEngine stb)
target_link_libraries(TmingEngine ImGui)
target_link_libraries(TmingEngine gl3w)
target_link_libraries(TmingEngine glm)
target_link_libraries(TmingEngine ScriptEngine)
target_link_libraries(TmingEngine assimp)
target_link_libraries(TmingEngine TextEditor)
target_link_libraries(TmingEngine ImNodes)
target_link_libraries(TmingEngine angelscript)
target_link_libraries(TmingEngine tgaimage)
target_link_libraries(TmingEngine ${Mono})

add_definitions(-DTmingEngineLib)
add_definitions(-DGLFW_INCLUDE_NONE)



