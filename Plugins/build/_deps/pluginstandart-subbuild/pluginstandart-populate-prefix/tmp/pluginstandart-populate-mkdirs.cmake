# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-src"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-build"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/tmp"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src"
  "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/leveophan/MyProjects/SuperProject/GraphicEditor/Plugins/build/_deps/pluginstandart-subbuild/pluginstandart-populate-prefix/src/pluginstandart-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
