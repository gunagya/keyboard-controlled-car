#include <ros.h>
#include "std_msgs/Int16.h"

bool l = false, r = false, di = false, du = false;
int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
int leftMotor  = 11;
int rightMotor = 10;

ros::NodeHandle nh;

void call_move(){
  if (l == true && r == true && di == true && du == true){
    turn(v1, v2, v4, v3);
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
    //nh.loginfo(sv1);
}


void intCallback2(const std_msgs::Int16& value){
    v2 = value.data;
    String sv2 = String(v2);
    r = true;
    call_move();
    //nh.loginfo(sv2);
}


void intCallback3(const std_msgs::Int16& value){
    v3 = value.data;
    String sv3 = String(v3);
    du = true;
    call_move();
    //nh.loginfo(sv3);
}


void intCallback4(const std_msgs::Int16& value){
    v4 = value.data;
    String sv4 = String(v4);
    di = true;
    call_move();
    //nh.loginfo(sv4);
}

ros::Subscriber<std_msgs::Int16> sub1("lspd", intCallback1);
ros::Subscriber<std_msgs::Int16> sub2("rspd", intCallback2);
ros::Subscriber<std_msgs::Int16> sub3("dir", intCallback3);
ros::Subscriber<std_msgs::Int16> sub4("dur", intCallback4);

void setup() {
  // put your setup code here, to run once:
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  analogWrite(leftMotor, 128);
  analogWrite(rightMotor, 128);
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
}

void loop() {
//  // put your main code here, to run repeatedly:
//  forward(75, 2000);
//  //delay(2000);
//  turn(75, 25, 2000, 1);
//  delay(2000);
//  turn(25, 75, 2000, 1);
//  delay(2000);
    nh.spinOnce();
    delay(1);
}

void stahp(){
  analogWrite(leftMotor, 127);
  analogWrite(rightMotor, 127);
}

void stahp_slow(){
  analogWrite(leftMotor, 128);
  analogWrite(rightMotor, 128);
}

void forward(int spd, int dur){
  analogWrite(leftMotor, 128+spd);
  analogWrite(rightMotor, 128+spd);
  delay(dur);
  stahp();
}

void turn(int lspd, int rspd, int dur, int dir) {
  analogWrite(leftMotor, 128+(dir*lspd));
  analogWrite(rightMotor, 128+(dir*rspd));
  delay(dur);
  stahp();
}

void backward(int spd, int dur){
  analogWrite(leftMotor, 128-spd);
  analogWrite(rightMotor, 128-spd);
  delay(dur);
  stahp();
}
