cmake_minimum_required(VERSION 3.5)
project(rviz_plugin_examples)

###################
# compile options #
###################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -DEIGEN_RUNTIME_NO_MALLOC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fno-asm")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

###################
# Depend packages #
###################
find_package(ament_cmake REQUIRED)
find_package(class_loader REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rviz2 REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(Eigen3 REQUIRED)

ament_export_dependencies(class_loader REQUIRED)
ament_export_dependencies(pluginlib REQUIRED)
ament_export_dependencies(rclcpp REQUIRED)
ament_export_dependencies(std_msgs REQUIRED)
ament_export_dependencies(rviz2 REQUIRED)
ament_export_dependencies(Eigen3 REQUIRED)

###############
# Qt settings #
###############
find_package(Qt5 ${rviz_QT_VERSION} REQUIRED Core Widgets)
macro(qt_wrap_ui)
  qt5_wrap_ui(${ARGN})
endmacro()
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(-DQT_NO_KEYWORDS)
# cmake settings #
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#########
# Build #
#########
# plugin export #
pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

include_directories(
  include
)
set(HEADERS
  include/rviz_plugin_examples/dial_panel.h
)
qt5_wrap_ui(UIC_FILES
  src/ui/dial_panel.ui
)
set(SOURCE_FILES
  src/dial_panel.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADERS} ${UIC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
ament_target_dependencies(${PROJECT_NAME}
  std_msgs
  rviz2
  Qt5
  pluginlib
)
target_include_directories(${PROJECT_NAME} PRIVATE "${OGRE_PREFIX_DIR}/include")

###########
# Install #
###########
install(DIRECTORY icons DESTINATION share/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

ament_export_libraries(
  ${PROJECT_NAME}
  )
ament_package()
