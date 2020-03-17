#include <stdio.h>
#include <stdlib.h>
#include "ros/ros.h"
#include "std_msgs/Int16.h"

ros::Publisher pub_1;
ros::Publisher pub_2;
ros::Publisher pub_3;
ros::Publisher pub_4;

void publisher(std_msgs::Int16 leftMotorForw, std_msgs::Int16 leftMotorBack, std_msgs::Int16 rightMotorForw, std_msgs::Int16 rightMotorBack){
    pub_1.publish(leftMotorForw);
    pub_2.publish(leftMotorBack);
    pub_3.publish(rightMotorForw);
    pub_4.publish(rightMotorBack);
    ROS_INFO("Published: [%d] [%d] [%d] [%d]", leftMotorForw.data, leftMotorBack.data, rightMotorForw.data, rightMotorBack.data);
}

void forward_down(){
    std_msgs::Int16 leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack;
    leftMotorForw.data = 1;
    leftMotorBack.data = 0;
    rightMotorForw.data = 1;
    rightMotorBack.data = 0;
    ROS_INFO("Published: [%d] [%d] [%d] [%d]", leftMotorForw.data, leftMotorBack.data, rightMotorForw.data, rightMotorBack.data);
    publisher(leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack);
}

void back_down(){
    std_msgs::Int16 leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack;
    leftMotorForw.data = 0;
    leftMotorBack.data = 1;
    rightMotorForw.data = 0;
    rightMotorBack.data = 1;
    publisher(leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack);
}

void right_down(){
    std_msgs::Int16 leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack;
    leftMotorForw.data = 1;
    leftMotorBack.data = 0;
    rightMotorForw.data = 0;
    rightMotorBack.data = 1;
    publisher(leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack);
}

void left_down(){
    std_msgs::Int16 leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack;
    leftMotorForw.data = 0;
    leftMotorBack.data = 1;
    rightMotorForw.data = 1;
    rightMotorBack.data = 0;
    publisher(leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack);
}

void key_down_callback(const std_msgs::Int16::ConstPtr& value){
    int command = value->data;
    if (command == 1){
        forward_down();
    }
    else if (command == 2){
        left_down();
    }
    else if (command == 3){
        back_down();
    }
    else if (command == 4){
        right_down();
    }
}

void key_up_callback(const std_msgs::Int16::ConstPtr& value){    
    std_msgs::Int16 leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack;
    leftMotorForw.data = 0;
    leftMotorBack.data = 0;
    rightMotorForw.data = 0;
    rightMotorBack.data = 0;
    publisher(leftMotorForw, leftMotorBack, rightMotorForw, rightMotorBack);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "arrayPublisher");
    ros::NodeHandle nh;
    
    ::pub_1 = nh.advertise<std_msgs::Int16>("/leftMotorForw", 100);
    ::pub_2 = nh.advertise<std_msgs::Int16>("/leftMotorBack", 100);
    ::pub_3 = nh.advertise<std_msgs::Int16>("/rightMotorForw", 100);
    ::pub_4 = nh.advertise<std_msgs::Int16>("/rightMotorBack", 100);

    ros::Subscriber sub1 = nh.subscribe("keydown_pub", 100, key_down_callback);
    ros::Subscriber sub2 = nh.subscribe("keyup_pub", 100, key_up_callback);

    while(ros::ok()){
        ros::spin();    
    }
}
