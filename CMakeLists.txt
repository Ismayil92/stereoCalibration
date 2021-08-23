cmake_minimum_required(VERSION 3.10.2)
project(Camera_Calibration)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(OpenCV_DIR /opt/opencv/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Threads REQUIRED)

message(STATUS "OpenCV library status:")

message(STATUS "    config: ${OpenCV_DIR}")

message(STATUS "    version: ${OpenCV_VERSION}")

message(STATUS "    libraries: ${OpenCV_LIBS}")

message(STATUS "    include path: ${CMAKE_CURRENT_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS}")




set(calibration_LIBS  
src/calibration_window.cpp
src/camera_config.cpp
include/calibration_window.hpp
include/ui_calibration.hpp
include/camera_config.hpp
)

#set(CMAKE_PREFIX_PATH /usr/include/aarch-linux-gnu/qt5)
add_library(calibration_LIBRARY ${calibration_LIBS})
target_include_directories(calibration_LIBRARY PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS} ${Qt5Gui_DEFINITIONS})
# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


# To find jsoncpp libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

add_executable(calibrate_camera src/main.cpp)
target_include_directories(calibrate_camera PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}  
  ${JSONCPP_INCLUDE_DIRS}
)
target_link_libraries(calibrate_camera calibration_LIBRARY Threads::Threads ${OpenCV_LIBS} ${JSONCPP_LIBRARIES} ${Qt5Widgets_LIBRARIES})

