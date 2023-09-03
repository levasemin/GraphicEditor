cmake_minimum_required(VERSION 3.25)

file(GLOB tool_lib_src "src/*/*.cpp" )
file(GLOB tool_lib_include "include/*/*.hpp" )

file(GLOB children "include/*")
set(dirlist "")
foreach(child ${children})
  if(IS_DIRECTORY ${curdir}/${child})
    list(APPEND dirlist ${child})
    endif()
endforeach()


add_library(tool_lib SHARED ${tool_lib_src} ${tool_lib_include})
target_include_directories(tool_lib PUBLIC . ${dirlist})