cmake_minimum_required(VERSION 3.0.2)
project(pointpub)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pointpub
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pointpub src/pointpub.cpp)
target_link_libraries(pointpub ${catkin_LIBRARIES})