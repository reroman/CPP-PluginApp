cmake_minimum_required( VERSION 3.5 )
project( PluginApp CXX )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_COMPILER "g++" )

# Establece la versión
set( PluginApp_VERSION_MAJOR 1 )
set( PluginApp_VERSION_MINOR 0 )

# Directorio de includes: El directorio de fuentes
include_directories( "${PROJECT_SOURCE_DIR}" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -U__STRICT_ANSI__" )

# Crear ejecutable
add_executable( figures FigureLoader.cpp main.cpp )
if( UNIX )
	target_link_libraries( figures dl ) # -ldl
endif( UNIX )

option( BUILD_PLUGINS "Build a few plugins to test" ON )
if( BUILD_PLUGINS )
	message( "Configuring plugins" )
	add_subdirectory( plugins )
endif( BUILD_PLUGINS )
