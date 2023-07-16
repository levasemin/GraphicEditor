project(CUSTOM_LIB)
cmake_minimum_required(VERSION 3.25)

include(FetchContent)


FetchContent_Declare(
  commonTools
  GIT_REPOSITORY https://github.com/mishaglik/Elpidifor-s-legacy.git
  GIT_TAG        main
)

FetchContent_GetProperties(commonTools)
FetchContent_Populate(commonTools)

FetchContent_Declare(
  glib
  GIT_REPOSITORY https://github.com/levasemin/Graphic-Library.git
  GIT_TAG        standart_2.0
)

FetchContent_GetProperties(glib)
FetchContent_Populate(glib)

# include_directories(build/_deps/commontools-src)
add_subdirectory(build/_deps/glib-src/)

file(GLOB glib_SRC "*/*.cpp")
file(GLOB glib_LIB "*/*.hpp")

file(GLOB children "*")
set(dirlist "")
foreach(child ${children})
  if(IS_DIRECTORY ${curdir}/${child})
    list(APPEND dirlist ${child})
    message(${child})
    endif()
endforeach()

# include_directories(build/_deps/commontools-src/)
add_library(glib_cust ${glib_LIB} ${glib_SRC})
target_include_directories(glib_cust PUBLIC ${dirlist} PUBLIC build/_deps/commontools-src/)
target_link_libraries(glib_cust PUBLIC glib)

# add_executable(main main.cpp)
# target_link_libraries(main PUBLIC glib_cust)