cmake_minimum_required(VERSION 3.30.4.0)
cmake_policy(SET CMP0091 OLD)
cmake_policy(SET CMP0141 OLD)
cmake_policy(SET CMP0126 OLD)
cmake_policy(SET CMP0128 OLD)
project(CMAKE_TRY_COMPILE CXX)
set_property(DIRECTORY PROPERTY INCLUDE_DIRECTORIES "")
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1")
set(CMAKE_EXE_LINKER_FLAGS "/machine:x64")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXE_LINKER_FLAGS}")
include_directories(${INCLUDE_DIRECTORIES})
set(CMAKE_SUPPRESS_REGENERATION 1)
link_directories(${LINK_DIRECTORIES})
cmake_policy(SET CMP0065 NEW)
cmake_policy(SET CMP0083 OLD)
cmake_policy(SET CMP0155 OLD)
cmake_policy(SET CMP0157 OLD)
include("${CMAKE_ROOT}/Modules/Internal/HeaderpadWorkaround.cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/admin/bul/graph-coloring/GraphColoring/CMakeFiles/CMakeScratch/TryCompile-frheqx")
add_executable(cmTC_846a9)
target_sources(cmTC_846a9 PRIVATE
  "C:/Program Files/CMake/share/cmake-3.30/Modules/CMakeCXXCompilerABI.cpp"
)
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/cmTC_846a9_$<UPPER_CASE:$<CONFIG>>_loc"
     CONTENT $<TARGET_FILE:cmTC_846a9>)
target_link_libraries(cmTC_846a9 ${LINK_LIBRARIES})
