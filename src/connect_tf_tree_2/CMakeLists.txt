cmake_minimum_required(VERSION 3.0.2)
project(connect_tf_tree_2)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  std_msgs
  tf2
  tf2_geometry_msgs
  tf2_ros
        nav_msgs
)

catkin_package(
 CATKIN_DEPENDS geometry_msgs roscpp std_msgs tf2 tf2_geometry_msgs tf2_ros nav_msgs
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(connect_tf_tree_2 src/connection_2.cpp)
target_link_libraries(connect_tf_tree_2 ${catkin_LIBRARIES})