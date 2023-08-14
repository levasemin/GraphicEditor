project(CUSTOM_LIB)
cmake_minimum_required(VERSION 3.25)

file(GLOB glib_SRC "src/*/*.cpp")
file(GLOB glib_LIB "include/*/*.hpp")

file(GLOB children "include/*")
set(dirlist "")
foreach(child ${children})
  if(IS_DIRECTORY ${curdir}/${child})
    list(APPEND dirlist ${child})
    message(${child})
    endif()
endforeach()

add_library(glib_cust ${glib_LIB} ${glib_SRC})
target_link_libraries(glib_cust PUBLIC -lboost_system -lboost_date_time -lboost_thread -lboost_serialization -lsfml-graphics -lsfml-window -lsfml-system)
target_include_directories(glib_cust PUBLIC ${dirlist} HistoryManager/)