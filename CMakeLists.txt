cmake_minimum_required(VERSION 3.25)

project(GraphicEditor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -ldl " CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)

add_subdirectory(src/Custom_Library)

add_executable(geditor src/GraphEditor/create_color_picker.cpp 
                       src/GraphEditor/create_file_combobox.cpp
                       src/GraphEditor/create_windows.cpp
                       src/main.cpp)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(geditor PUBLIC sfml-network sfml-audio sfml-graphics sfml-window sfml-system -ldl)
endif()

target_link_libraries(geditor PUBLIC glib_cust -ldl)