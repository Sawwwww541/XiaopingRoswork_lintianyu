execute_process(COMMAND "/home/lty/xiaoping_ws/build/turtlebot3-master/turtlebot3_example/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/lty/xiaoping_ws/build/turtlebot3-master/turtlebot3_example/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
