cmake_minimum_required(VERSION 3.12)

project(ProyectTemplate CXX C)

#Set GLFW Variables
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

#Glad Library
set(GLAD_SOURCES vendor/glad/src/glad.c)
add_library(glad ${GLAD_SOURCES})

#Libraries subdirectories
add_subdirectory(vendor/glfw)
#add_subdirectory(vendor/glm)

#Include directories for the library
include_directories(vendor/imgui)
include_directories(vendor/imgui/backends)
include_directories(vendor/glad/include)
include_directories(deps/src/glfw/include)
include_directories(vendor/spdlog/include)
include_directories(vendor/glm)
include_directories(Core/src)

#Set Properties
set_property(TARGET glad          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(TARGET glfw          PROPERTY FOLDER "ThirdPartyLibraries")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define a macro in CMake
add_compile_definitions(RENDERER_API_OPENGL)
add_compile_definitions(OPERATIVE_SYSTEM_WINDOWS)

add_subdirectory(App)
add_subdirectory(Core)
