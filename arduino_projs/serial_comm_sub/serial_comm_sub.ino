#include <ros.h>
#include "std_msgs/Int16.h"

ros::NodeHandle nh;

int v1 = 0;
void intCallback1(const std_msgs::Int16& value){
    v1 = value.data;
    //ROS_INFO("V1: [%d]", v1);
}

int v2 = 0;
void intCallback2(const std_msgs::Int16& value){
    v2 = value.data;
    //ROS_INFO("V2: [%d]", v2);
}

int v3 = 0;
void intCallback3(const std_msgs::Int16& value){
    v3 = value.data;
    //ROS_INFO("V3: [%d]", v3);
}

int v4 = 0;
void intCallback4(const std_msgs::Int16& value){
    v4 = value.data;
    //ROS_INFO("V4: [%d]", v4);
}

ros::Subscriber<std_msgs::Int16> sub1("/random_number1", intCallback1);
ros::Subscriber<std_msgs::Int16> sub2("/random_number2", intCallback2);
ros::Subscriber<std_msgs::Int16> sub3("/random_number3", intCallback3);
ros::Subscriber<std_msgs::Int16> sub4("/random_number4", intCallback4);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(500);
}
