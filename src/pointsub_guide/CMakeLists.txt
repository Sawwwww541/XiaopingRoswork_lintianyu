cmake_minimum_required(VERSION 3.0.2)
project(pointsub_guide)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  tf2
        std_msgs
        tf2_ros
        tf2_geometry_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pointsub_guide
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp tf2 std_msgs tf2_ros tf2_geometry_msgs
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pointsub_guide src/pointsub_guide.cpp)
target_link_libraries(pointsub_guide ${catkin_LIBRARIES})