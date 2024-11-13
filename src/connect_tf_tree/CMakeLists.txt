cmake_minimum_required(VERSION 3.0.2)
project(connect_tf_tree)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  tf2
        tf2_ros
        tf2_geometry_msgs
        std_msgs
        geometry_msgs
        nav_msgs
)

catkin_package(
        CATKIN_DEPENDS roscpp tf2 tf2_ros tf2_geometry_msgs geometry_msgs nav_msgs std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(connect_tf_tree src/connection.cpp)
target_link_libraries(connect_tf_tree ${catkin_LIBRARIES})