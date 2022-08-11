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
	"src/headers/matrix4.h" 
	"src/matrix4.cpp" 
	"src/headers/segment2D.h"
	"src/segment2D.cpp"
	"src/headers/vertex.h"
	"src/headers/joint2D.h"
	"src/joint2D.cpp" 
	"src/headers/transform.h"
	"src/headers/vector2.h" 
	"src/vector2.cpp"
	"src/headers/vector3.h"
	"src/vector3.cpp"
	"src/transform.cpp" 
	"src/headers/color.h"
	"src/headers/object2D.h"
	"src/object2D.cpp" 
	"src/headers/fabrik2D.h" 
	"src/fabrik2D.cpp"
	"src/headers/node.h"
	"src/node.cpp" 
	"src/headers/tree.h" 
	"src/headers/target2D.h" 
	"src/headers/object.h"
	"src/object.cpp" 
	"src/headers/object3D.h"
	"src/object3D.cpp"
	"src/headers/joint3D.h"
	"src/headers/segment3D.h"
	"src/joint3D.cpp" 
	"src/segment3D.cpp"
	"src/headers/target3D.h"
	"src/target3D.cpp"
	"src/headers/fabrik3D.h" 
	"src/fabrik3D.cpp" 
	"src/headers/fabrik.h" 
	"src/fabrik.cpp"
	"src/headers/scene.h" 
	"src/scene.cpp" 
	"src/headers/camera.h" 
	"src/camera.cpp" 
	"src/headers/orthographicCamera.h"
	"src/orthographicCamera.cpp" 
	"src/headers/perspectiveCamera.h"
	"src/perspectiveCamera.cpp"
	"src/headers/hinge2D.h" 
	"src/hinge2D.cpp"
	"src/headers/constraint2D.h" 
	"src/constraint2D.cpp" 
	"src/headers/mathf.h" 
	"src/mathf.cpp" "src/headers/constraint3D.h" "src/constraint3D.cpp" "src/headers/hinge3D.h" "src/hinge3D.cpp" "src/headers/twist3D.h" "src/twist3D.cpp")

target_link_libraries(FABRIK OpenGL::GL glew glfw)

add_custom_command(TARGET FABRIK POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
				${FABRIK_SOURCE_DIR}/src/shaders ${PROJECT_BINARY_DIR}/shaders
	COMMAND ${CMAKE_COMMAND} -E copy
				${PROJECT_BINARY_DIR}/bin/glew32d.dll ${PROJECT_BINARY_DIR}/glew32d.dll
)