#include <ros.h>
#include "std_msgs/Int16.h"

ros::NodeHandle nh;

int v1 = 0;
void intCallback1(const std_msgs::Int16& value){
    v1 = value.data;
    String sv1 = String(v1);
    nh.loginfo(sv1);
}

int v2 = 0;
void intCallback2(const std_msgs::Int16& value){
    v2 = value.data;
    String sv2 = String(v2);
    nh.loginfo(sv2);
}

int v3 = 0;
void intCallback3(const std_msgs::Int16& value){
    v3 = value.data;
    String sv3 = String(v3);
    nh.loginfo(sv3);
}

int v4 = 0;
void intCallback4(const std_msgs::Int16& value){
    v4 = value.data;
    String sv4 = String(v4);
    nh.loginfo(sv4);
}

ros::Subscriber<std_msgs::Int16> sub1("lspd", intCallback1);
ros::Subscriber<std_msgs::Int16> sub2("rspd", intCallback2);
ros::Subscriber<std_msgs::Int16> sub3("dir", intCallback3);
ros::Subscriber<std_msgs::Int16> sub4("dur", intCallback4);

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
