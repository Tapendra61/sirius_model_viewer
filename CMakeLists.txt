cmake_minimum_required(VERSION 3.5...4.2)
project(sirius_model_viewer LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(model_viewer
	src/main.cpp
	src/glad.c
	src/stbi.cpp
	src/core/application.cpp
	src/core/window.cpp
	src/core/input.cpp
	src/renderer/renderer.cpp
	src/renderer/shader.cpp
	src/renderer/camera.cpp
	src/renderer/texture.cpp
	src/renderer/material.cpp
	src/controllers/camera_controller.cpp
	src/buffers/vertex_buffer.cpp
	src/buffers/index_buffer.cpp
	src/buffers/vertex_array.cpp
	src/model/mesh.cpp
	src/model/model.cpp
	src/components/transform.cpp
	
	# IMGUI
	src/imgui.cpp
	src/imgui_draw.cpp
	src/imgui_impl_glfw.cpp
	src/imgui_impl_opengl3.cpp
	src/imgui_tables.cpp
	src/imgui_widgets.cpp
	src/ImGuiFileDialog.cpp
)

target_compile_features(model_viewer PRIVATE cxx_std_20)

target_include_directories(model_viewer PRIVATE
   ${CMAKE_SOURCE_DIR}/include
   ${CMAKE_SOURCE_DIR}/dependencies/include
   ${CMAKE_SOURCE_DIR}/dependencies/include/common
   ${CMAKE_SOURCE_DIR}/dependencies/include/imgui
   ${CMAKE_SOURCE_DIR}/dependencies/include/imgui/backend
)

target_link_libraries(model_viewer PRIVATE
	${CMAKE_SOURCE_DIR}/dependencies/libs/glfw3.lib
	${CMAKE_SOURCE_DIR}/dependencies/libs/assimp.lib
	${CMAKE_SOURCE_DIR}/dependencies/libs/zlibstatic.lib
)