# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-src"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-build"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/tmp"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/src/utils-populate-stamp"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/src"
  "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/src/utils-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/src/utils-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/levce/projectsDED/GraphicEditor/src/PythonPlug/ESL-PyPlug-master/build/_deps/utils-subbuild/utils-populate-prefix/src/utils-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
