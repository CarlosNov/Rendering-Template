cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c??)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)

add_library(Core SHARED ${SRC_FILES} ${HEADER_FILES})

# Set the include directories for the DLL project
target_include_directories(Core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
# Set the library link for the DLL project
target_link_libraries(Core glfw glad)

# Set the output directory for the DLL
set_target_properties(Core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

set_target_properties(Core PROPERTIES
    OUTPUT_NAME "Core"
    PREFIX ""
    SUFFIX ".dll"
)

target_precompile_headers(Core PRIVATE src/CorePCHeader.h)

# Folder structure
ASSIGN_SOURCE_GROUP("${SRC_FILES}")
ASSIGN_SOURCE_GROUP("${HEADER_FILES}")

#Compilation definitions
add_compile_definitions(CORE_PLATFORM_WINDOWS)
add_compile_definitions(CORE_BUILD_DLL)
add_compile_definitions(CORE_DEBUG)
