cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

set(CMAKE_VERBOSE_MAKEFILE TRUE)
#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()
#SET(wxWidgets_ROOT_DIR /home/amilab/wxWidgets/builddir)
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})#honek 2.8 hartzen du
include_directories( ${wxWidgets_INCLUDE_DIRS} )
#include_directories( /home/amilab/wxWidgets/builddir/include/wx-2.9 )
#link_directories( /home/amilab/wxWidgets/builddir/lib )

#include_directories( ${wxWidgets_INCLUDE_DIRS} ) ##honek 2.8a hartzen du
#MESSAGE(${wxWidgets_USE_FILE})
#MESSAGE("include_dirs:"${wxWidgets_INCLUDE_DIRS})
#MESSAGE(${wxWidgets_LIBRARIES})

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
rosbuild_add_executable(kinecta src/Main.cpp src/ui.cpp src/camview.cpp)
rosbuild_add_executable(image_resizer src/image_resizer.cpp)
#get_target_property(_link_flags kinecta LINK_FLAGS)
#MESSAGE( STATUS "_link_flags: " ${_link_flags} )
#set(_link_flags "${_link_flags} -L/home/amilab/wxWidgets/builddir/lib")
#MESSAGE( STATUS "_link_flags2: " ${_link_flags} )
#set_target_properties(${kinecta} PROPERTIES LINK_FLAGS "${_link_flags}")
#MESSAGE( STATUS "PROPERTIES_LINK_FLAGS: " ${PROPERTIES_LINK_FLAGS} )
#target_link_libraries(kinecta  pthread symbolic-functions wx_baseu wx_baseu_net wx_baseu_xml wx_gtk2u_core wx_gtk2u_adv wx_gtk2u_html wx_gtk2u_qa wx_gtk2u_xrc wx_gtk2u_aui wx_gtk2u_richtext)

#message(STATUS "wxWidgets_LIBRARIES....................${wxWidgets_LIBRARIES}")
target_link_libraries(kinecta ${wxWidgets_LIBRARIES})
