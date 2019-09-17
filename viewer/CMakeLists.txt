cmake_minimum_required(VERSION 3.10)

set(TARGET_NAME viewer)

project(${TARGET_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)

add_executable(${TARGET_NAME}
							 ${TARGET_NAME}.cpp
							 ../3rdparty/imgui/imgui.cpp
							 ../3rdparty/imgui/imgui_draw.cpp
							 ../3rdparty/imgui/imgui_widgets.cpp
							 ../3rdparty/imgui/examples/imgui_impl_glfw.cpp
							 ../3rdparty/imgui/examples/imgui_impl_opengl3.cpp
							 ../3rdparty/imgui/examples/libs/gl3w/GL/gl3w.c
							)

target_include_directories(${TARGET_NAME}
													 PRIVATE
													 ../3rdparty/imgui/
													 ../3rdparty/imgui/examples/
													 ../3rdparty/imgui/examples/libs/gl3w/
													)

target_link_libraries(${TARGET_NAME}
											-lGL
											-lGLU
											-lglfw3
											-lX11
											-ldl
											-lpthread
											-lm
										 )