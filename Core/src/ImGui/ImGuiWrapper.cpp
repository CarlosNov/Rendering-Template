#include "CorePCHeader.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>

#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#include "imgui_tables.cpp"
#include "imgui_widgets.cpp"