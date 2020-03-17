# keyboard-controlled-car
A package implemented in ROS that enables communication between the host computer and a robot car to establish keyboard control

To compile, run catkin_make in your catkin workspace.

The package requires four ROS nodes to be setup. Run the following commands on different terminals:-

1. roscore: Master node
2. rosrun comm_test keyboard_publisher: Read inputs from keyboard
3. rosrun comm_test key_to_ard: Map keyboard inputs to motor values to allow movement and rotation
4. rosrun rosserial_python serial_node.py /dev/ttyUSB0: Allows serial port communication with Arduino

Don't forget to source devel/setup.bash in the terminals!
