cmake_minimum_required(VERSION 3.5...4.2)
project(sirius_model_viewer LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(model_viewer
	src/main.cpp
	src/glad.c
	src/core/application.cpp
	src/core/window.cpp
	src/core/input.cpp
	src/renderer/renderer.cpp
	src/renderer/shader.cpp
	src/renderer/camera.cpp
)

target_compile_features(model_viewer PRIVATE cxx_std_20)

target_include_directories(model_viewer PRIVATE
   ${CMAKE_SOURCE_DIR}/include
   ${CMAKE_SOURCE_DIR}/dependencies/include
)

target_link_libraries(model_viewer PRIVATE
	${CMAKE_SOURCE_DIR}/dependencies/libs/glfw3.lib
	${CMAKE_SOURCE_DIR}/dependencies/libs/assimp.lib
)