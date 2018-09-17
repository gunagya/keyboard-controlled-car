#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Int16.h"

int min=1;
int max=256;
int rand_no;

int random_number(){
  rand_no= rand() % 256;
  return rand_no;
}
 
int main(int argc, char **argv){
    ros::init(argc, argv, "arrayPublisher");
    ros::NodeHandle nh;
    
    ros::Publisher pub_1 = nh.advertise<std_msgs::Int16>("/random_number1", 100);
    ros::Publisher pub_2 = nh.advertise<std_msgs::Int16>("/random_number2", 100);
    ros::Publisher pub_3 = nh.advertise<std_msgs::Int16>("/random_number3", 100);
    ros::Publisher pub_4 = nh.advertise<std_msgs::Int16>("/random_number4", 100);
    while(ros::ok()){
        std_msgs::Int16 rand_msg;

        rand_msg.data = random_number();
        pub_1.publish(rand_msg);
        ROS_INFO("V1: [%d]", rand_msg.data);

        rand_msg.data = random_number();
        pub_2.publish(rand_msg);
        ROS_INFO("V1: [%d]", rand_msg.data);

        rand_msg.data = random_number();
        pub_3.publish(rand_msg);
        ROS_INFO("V1: [%d]", rand_msg.data);

        rand_msg.data = random_number();
        pub_4.publish(rand_msg);
        ROS_INFO("V1: [%d]", rand_msg.data);
        
        ROS_INFO("Published!");
        ros::spinOnce();
        sleep(2);        
    }
}