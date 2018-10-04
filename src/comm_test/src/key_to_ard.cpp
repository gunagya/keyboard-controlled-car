#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Int16.h"

ros::Publisher pub_1;
ros::Publisher pub_2;
ros::Publisher pub_3;
ros::Publisher pub_4;

int max_spd = 52;
int updatation_rate= 10;
int turn_speed = 4;

int min=1;
int max=256;

void publisher(std_msgs::Int16 lspd, std_msgs::Int16 rspd, std_msgs::Int16 dur, std_msgs::Int16 dir){
    pub_1.publish(lspd);
    pub_2.publish(rspd);
    pub_3.publish(dur);
    pub_4.publish(dir);
    ROS_INFO("Published: [%d] [%d] [%d] [%d]", lspd.data, rspd.data, dur.data, dir.data);
}

void forward_down(){
    std_msgs::Int16 lspd, rspd, dur, dir;
    lspd.data = max_spd;
    rspd.data = max_spd;
    dur.data = updatation_rate;
    dir.data = 1;
    ROS_INFO("Published: [%d] [%d] [%d] [%d]", lspd.data, rspd.data, dur.data, dir.data);
    publisher(lspd, rspd, dur, dir);
}

void back_down(){
    std_msgs::Int16 lspd, rspd, dur, dir;
    lspd.data = max_spd;
    rspd.data = max_spd;
    dur.data = updatation_rate;
    dir.data = -1;
    publisher(lspd, rspd, dur, dir);
}

void right_down(){
    std_msgs::Int16 lspd, rspd, dur, dir;
    lspd.data = max_spd;
    rspd.data = max_spd/turn_speed;
    dur.data = updatation_rate;
    dir.data = 1;
    publisher(lspd, rspd, dur, dir);
}

void left_down(){
    std_msgs::Int16 lspd, rspd, dur, dir;
    lspd.data = max_spd/turn_speed;
    rspd.data = max_spd;
    dur.data = updatation_rate;
    dir.data = 1;
    publisher(lspd, rspd, dur, dir);
}

void key_up(){
    std_msgs::Int16 lspd, rspd, dur, dir;
    lspd.data = 0;
    rspd.data = 0;
    dur.data = updatation_rate;
    dir.data = 1;
    publisher(lspd, rspd, dur, dir);
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
    key_up();
}

int main(int argc, char **argv){
    ros::init(argc, argv, "arrayPublisher");
    ros::NodeHandle nh;
    
    ros::Publisher pub_1 = nh.advertise<std_msgs::Int16>("/lspd", 100);
    ros::Publisher pub_2 = nh.advertise<std_msgs::Int16>("/rspd", 100);
    ros::Publisher pub_3 = nh.advertise<std_msgs::Int16>("/dur", 100);
    ros::Publisher pub_4 = nh.advertise<std_msgs::Int16>("/dir", 100);

    ros::Subscriber sub1 = nh.subscribe("keydown_pub", 100, key_down_callback);
    ros::Subscriber sub2 = nh.subscribe("keyup_pub", 100, key_up_callback);

    while(ros::ok()){
        ros::spin();    
    }
}