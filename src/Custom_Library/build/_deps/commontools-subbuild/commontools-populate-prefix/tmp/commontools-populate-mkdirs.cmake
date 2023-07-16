# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-src"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-build"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/tmp"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/src/commontools-populate-stamp"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/src"
  "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/src/commontools-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/src/commontools-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/leveophan/MyProjects/GraphicEditor/src/Custom_Library/build/_deps/commontools-subbuild/commontools-populate-prefix/src/commontools-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
