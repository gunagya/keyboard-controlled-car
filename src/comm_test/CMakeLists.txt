cmake_minimum_required(VERSION 2.8.3)
project(comm_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospy
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})
add_dependencies(publisher comm_test_generate_messages_cpp)

add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber ${catkin_LIBRARIES})
add_dependencies(subscriber comm_test_generate_messages_cpp)

add_executable(key_to_ard src/key_to_ard.cpp)
target_link_libraries(key_to_ard ${catkin_LIBRARIES})
add_dependencies(key_to_ard comm_test_generate_messages_cpp)

add_executable(keyboard_subcriber_in_c src/keyboard_subcriber_in_c.cpp)
target_link_libraries(keyboard_subcriber_in_c ${catkin_LIBRARIES})
add_dependencies(key_to_ard comm_test_generate_messages_cpp)

catkin_install_python(PROGRAMS bin/keyboard_publisher
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

catkin_install_python(PROGRAMS bin/keyboard_subscriber
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
