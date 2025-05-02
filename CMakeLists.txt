cmake_minimum_required(VERSION 3.10)
project(GraphColoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW as a subdirectory
add_subdirectory(glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# More explicit include directory addition
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/glfw/include
)

# Create lists of source and header files
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with GLFW and OpenGL
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        glfw
        OpenGL::GL
)

# More explicit target include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/glfw/include
)

# Output configuration information
message(STATUS "Using GLFW from: ${CMAKE_SOURCE_DIR}/glfw")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
