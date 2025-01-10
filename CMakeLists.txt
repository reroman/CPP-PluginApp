cmake_minimum_required(VERSION 3.19)
project(
  PluginApp
  VERSION 2.0.0
  DESCRIPTION "Simple app extensible using plugins in C++"
  LANGUAGES CXX)

option(BUILD_PLUGINS "Build a few plugins to test" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add warnings
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()

# Plugin interface
add_library(figure_plugin INTERFACE Figure.hpp)
target_include_directories(figure_plugin INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Main program
add_executable(figures FigureLoader.hpp FigureLoader.cpp main.cpp)
target_link_libraries(figures PRIVATE figure_plugin)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(figures PRIVATE dl)
endif()

# Plugins
if(BUILD_PLUGINS)
  message(STATUS "Configuring plugins")
  add_subdirectory(plugins)
endif(BUILD_PLUGINS)
