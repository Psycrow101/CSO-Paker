cmake_minimum_required(VERSION 3.12.0)

project(csopak LANGUAGES CXX)

#
# Global paths
#
set(PAK_ROOT_DIR "${PROJECT_SOURCE_DIR}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#
# add source files to the project
#
set(PAK_SOURCES_BASE
    "sources/cmdparser.cpp" "sources/fsutils.cpp" "sources/main.cpp"
    "sources/pakfile.cpp" "sources/snow.cpp")

set(PAK_HEADERS_BASE
    "headers/cmdparser.hpp" "headers/fsutils.hpp" "headers/pakfile.hpp"
    "headers/pakview.hpp" "headers/snow.hpp" "headers/util.hpp")

file(GLOB PAK_ALL_SOURCES ${PAK_SOURCES_BASE} ${PAK_HEADERS_BASE})

source_group("Source Files" FILES ${PAK_SOURCES_BASE})
source_group("Header Files" FILES ${PAK_HEADERS_BASE})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

#
# Add executable to build.
#
add_executable(csopak ${PAK_ALL_SOURCES})

#
# Enable all warnings
#
if(MSVC)
  target_compile_options(csopak PRIVATE /W4)
else()
  target_compile_options(csopak PRIVATE -Wall -Wextra -pedantic)
endif()

#
# Setup include directories
#
target_include_directories(csopak PRIVATE "headers")
