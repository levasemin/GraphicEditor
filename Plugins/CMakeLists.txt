project(TOOLPAINT)
cmake_minimum_required(VERSION 3.25)

include(FetchContent)

FetchContent_Declare(
  PluginStandart
  GIT_REPOSITORY https://github.com/levasemin/PluginStandart.git
  GIT_TAG        master
)

FetchContent_GetProperties(PluginStandart)
FetchContent_Populate(PluginStandart)

include_directories(../build/_deps/pluginstandart-src)

add_library(paint_tool SHARED Paint.cpp Interpolator.cpp Interpolator.hpp)
add_compile_options(-fPIC)
target_include_directories(paint_tool PUBLIC .)