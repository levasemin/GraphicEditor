cmake_minimum_required(VERSION 3.1)

project(GraphicEditor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)

include(FetchContent)

if(CMAKE_BUILD_TYPE STREQUAL "Example")
  include_directories(../)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)
  message("Example mode on!")
else()
  FetchContent_Declare(
    commonTools
    GIT_REPOSITORY https://github.com/mishaglik/Elpidifor-s-legacy.git
    GIT_TAG        main
  )

  FetchContent_GetProperties(commonTools)
  if(NOT commonTools_POPULATED)
    FetchContent_Populate(commonTools)
    include_directories(./build/_deps/commontools-src)
  endif()
endif()

FetchContent_Declare(
  glib
  GIT_REPOSITORY https://github.com/levasemin/Graphic-Library.git
  GIT_TAG        standart_2.0
)

FetchContent_GetProperties(glib)
if(NOT glib_POPULATED)
  FetchContent_Populate(glib)
  add_subdirectory(${glib_SOURCE_DIR})
endif()

file(GLOB geditor_Custom_Widgets_SRC "src/Custom_Widgets/*.cpp")
file(GLOB geditor_Tool_SRC "src/Tool/*.cpp")
file(GLOB geditor_Tool_Widgets_SRC "./src/Tool/Widgets/*.cpp")
file(GLOB geditor_INC "./*/")

include_directories(./src/Custom_Widgets)
include_directories(./src/Tool)
include_directories(./src/Tool/Widgets)

add_executable(geditor 
                ./src/main.cpp
                ${geditor_Custom_Widgets_SRC}
                ${geditor_Tool_SRC}
                ${geditor_Tool_Widgets_SRC}
)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(geditor PUBLIC sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

target_link_libraries(geditor PUBLIC glib)
