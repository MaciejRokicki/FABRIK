cmake_minimum_required (VERSION 3.8)

project ("FABRIK")

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libraries/glfw-3.3.6)
add_subdirectory(libraries/glew-2.1.0/build/cmake)

include_directories(libraries/glew-2.1.0/include)

add_executable (
	FABRIK 
	"src/main.cpp"
	"src/headers/main.h"
	"src/headers/window.h"
	"src/window.cpp" 
	"src/headers/shaderProgram.h"
	"src/shaderProgram.cpp" 
	"src/headers/cameraProgram.h"  
	"src/headers/mat4.h" 
	"src/mat4.cpp" 
	"src/cameraProgram.cpp" 
	"src/headers/modelProgram.h" 
	"src/cameraModelProgram.cpp"
	"src/headers/segment.h"
	"src/segment.cpp"
	"src/headers/vertex.h"
	"src/headers/joint.h"
	"src/joint.cpp" 
	"src/headers/transform.h"
	"src/headers/vector2.h" 
	"src/vector2.cpp"
	"src/headers/vector3.h"
	"src/vector3.cpp"
	"src/transform.cpp" 
	"src/headers/color.h"
	"src/headers/model.h"
	"src/model.cpp" 
	"src/headers/fabrik2D.h" 
	"src/fabrik2D.cpp"
	"src/headers/node.h"
	"src/node.cpp" "src/headers/tree.h" "src/headers/target.h" "src/headers/chain2D.h")

target_link_libraries(FABRIK OpenGL::GL glew glfw)

add_custom_command(TARGET FABRIK POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
				${FABRIK_SOURCE_DIR}/src/shaders ${PROJECT_BINARY_DIR}/shaders
	COMMAND ${CMAKE_COMMAND} -E copy
				${PROJECT_BINARY_DIR}/bin/glew32d.dll ${PROJECT_BINARY_DIR}/glew32d.dll
)