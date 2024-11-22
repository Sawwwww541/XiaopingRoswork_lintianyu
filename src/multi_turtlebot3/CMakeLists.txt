cmake_minimum_required(VERSION 3.0.2)
project(multi_turtlebot3)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        geometry_msgs
        nav_msgs
        tf2
        tf2_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES multi_turtlebot3
CATKIN_DEPENDS roscpp std_msgs geometry_msgs nav_msgs tf2 tf2_ros
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(follower src/follower.cpp)
target_link_libraries(follower ${catkin_LIBRARIES})
target_include_directories(follower PUBLIC
        ${catkin_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include)