#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int16MultiArray.h"

int v1 = 0;
void intCallback1(const std_msgs::Int16::ConstPtr& value){
    v1 = value->data;
    ROS_INFO("V1: [%d]", v1);
}

int v2 = 0;
void intCallback2(const std_msgs::Int16::ConstPtr& value){
    v2 = value->data;
    ROS_INFO("V2: [%d]", v2);
}

int v3 = 0;
void intCallback3(const std_msgs::Int16::ConstPtr& value){
    v3 = value->data;
    ROS_INFO("V3: [%d]", v3);
}

int v4 = 0;
void intCallback4(const std_msgs::Int16::ConstPtr& value){
    v4 = value->data;
    ROS_INFO("V4: [%d]", v4);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "CommandReader");
    ROS_INFO("Initialized!");
    ros::NodeHandle nh;
    ros::Subscriber sub1 = nh.subscribe("/random_number1", 100, intCallback1);
    ros::Subscriber sub2 = nh.subscribe("/random_number2", 100, intCallback2);
    ros::Subscriber sub3 = nh.subscribe("/random_number3", 100, intCallback3);
    ros::Subscriber sub4 = nh.subscribe("/random_number4", 100, intCallback4);
    ROS_INFO("Created all topics");
    ros::spin();
    return 0;
}