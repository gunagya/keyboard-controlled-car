#include <ros.h>
#include "std_msgs/Int16.h"

bool l = false, r = false, di = false, du = false;
int v1 = 0, v2 = 0, v3 = 0, v4 = 0; 
#define leftMotorForw 11
#define rightMotorForw 8
#define leftMotorBack 12
#define rightMotorBack 9

ros::NodeHandle nh;

void call_move(){
  if (l == true && r == true && di == true && du == true){
    turn(v1, v2, v3, v4);
    l = false;
    r = false;
    di = false;
    du = false;
  }
}


void intCallback1(const std_msgs::Int16& value){
    v1 = value.data;
    String sv1 = String(v1);
    l = true;
    call_move();
}


void intCallback2(const std_msgs::Int16& value){
    v2 = value.data;
    String sv2 = String(v2);
    r = true;
    call_move();
}


void intCallback3(const std_msgs::Int16& value){
    v3 = value.data;
    String sv3 = String(v3);
    du = true;
    call_move();
}


void intCallback4(const std_msgs::Int16& value){
    v4 = value.data;
    String sv4 = String(v4);
    di = true;
    call_move();
}

ros::Subscriber<std_msgs::Int16> sub1("/leftMotorForw", intCallback1);
ros::Subscriber<std_msgs::Int16> sub2("/leftMotorBack", intCallback2);
ros::Subscriber<std_msgs::Int16> sub3("/rightMotorForw", intCallback3);
ros::Subscriber<std_msgs::Int16> sub4("/rightMotorBack", intCallback4); 

void setup() {
  pinMode(leftMotorForw, OUTPUT);
  pinMode(leftMotorBack, OUTPUT);
  pinMode(rightMotorForw, OUTPUT);
  pinMode(rightMotorBack, OUTPUT);
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4); 
}

void loop() {
    nh.spinOnce();
    delay(1);
}

void stahp(){             
  digitalWrite(leftMotorForw, 0); 
  digitalWrite(leftMotorBack, 0); 
  digitalWrite(rightMotorForw, 0);
  digitalWrite(rightMotorBack, 0);
}


void turn(int lMF, int lMB, int rMF, int rMB) {   
  digitalWrite(leftMotorForw, lMF);
  digitalWrite(leftMotorBack, lMB);
  digitalWrite(rightMotorForw, rMF);
  digitalWrite(rightMotorBack, rMB);
  delay(10);
}
