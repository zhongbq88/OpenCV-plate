cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)
set(libs "${CMAKE_SOURCE_DIR}/src/main/jniLibs")
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library(libopencv_java3 SHARED IMPORTED )
set_target_properties(libopencv_java3 PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libopencv_java3.so")

add_library(  ec-cv-lib
              SHARED
              src/main/cpp/cv-lib.cpp
              src/main/cpp/ImgColorPlateLocation.cpp
              src/main/cpp/ImgPlateLocation.cpp
              src/main/cpp/ImgPlateRecgnize.cpp
              src/main/cpp/ImgPlateMatches.cpp
              )

find_library(
              log-lib
              log )
target_link_libraries( # Specifies the target library.
                       cv-lib
                       log
                       jnigraphics
                       libopencv_java3
                       ${log-lib} )