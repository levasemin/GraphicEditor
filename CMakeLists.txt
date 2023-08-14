cmake_minimum_required(VERSION 3.25)

project(GraphicEditor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -ldl " CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)

include(FetchContent)

FetchContent_Declare(
  PluginStandart
  GIT_REPOSITORY https://github.com/levasemin/PluginStandart.git
  GIT_TAG        master
)

FetchContent_GetProperties(PluginStandart)
FetchContent_Populate(PluginStandart)

include_directories(build/_deps/pluginstandart-src)

FetchContent_Declare(
  glib
  GIT_REPOSITORY https://github.com/levasemin/Graphic-Library.git
  GIT_TAG        standart_2.0
)

FetchContent_GetProperties(glib)
FetchContent_Populate(glib)

add_subdirectory(lib/Custom_Library)
add_subdirectory(lib/Custom_Library/ToolLibrary)
add_subdirectory(build/_deps/glib-src)

add_compile_options(-ldl -export-dynamic -lboost_system -lboost_date_time -lboost_thread -lboost_serialization -lsfml-graphics -lsfml-window -lsfml-system)
add_executable(geditor src/GraphEditor/create_file_combobox.cpp
                       src/GraphEditor/create_windows.cpp
                       src/main.cpp)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(geditor PUBLIC sfml-network sfml-audio sfml-graphics sfml-window sfml-system -ldl)
endif()

target_link_libraries(tool_lib PUBLIC glib)
target_link_libraries(glib_cust PUBLIC tool_lib)
target_link_libraries(geditor PUBLIC glib_cust -ldl)