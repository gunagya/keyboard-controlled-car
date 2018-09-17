cmake_minimum_required(VERSION 2.8.3)
project(comm_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})
add_dependencies(publisher comm_test_generate_messages_cpp)

add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber ${catkin_LIBRARIES})
add_dependencies(subscriber comm_test_generate_messages_cpp)