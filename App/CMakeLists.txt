cmake_minimum_required(VERSION 3.12)

project(App)

include(../CMake/CommonMacros.txt)
include_directories(../Core/src)
include_directories(vendor/imgui)
include_directories(vendor/imgui/backends)
SETUP_APP(App "")

# Set the include directories for the executable project
target_include_directories(App PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the link directories for the executable project
target_link_directories(App PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Link the executable to the DLL
target_link_libraries(App Core)

add_compile_definitions(CORE_PLATFORM_WINDOWS)