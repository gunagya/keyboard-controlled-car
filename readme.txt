arduino_projs contains 3 folders, serial_comm_sub is the subscriber, serial_comm_pub is publisher and motor_config has the code for the motor movement.

To create these packages in catkin make, download the repo, extract it to a folder wks, and call catkin make in that folder. Then run "source devel/setup.bash" in command line and use rosrun comm_test publisher to call the publisher and rosrun comm_test subscriber to call the subscriber.
