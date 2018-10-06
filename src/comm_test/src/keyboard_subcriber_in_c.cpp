#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "ros/ros.h"
#include "std_msgs/Int16.h"

bool w_key = false, a_key = false, s_key = false, d_key = false;

void assignValue (int keycode, int* lspd_val, int* rspd_val, int* dir_val, int* dur_val)
{
	*dur_val=10;
	switch (keycode)
	{
		case 1: *lspd_val = 64; //128
			*rspd_val = 64; //128
			*dir_val = 1; 
			w_key = true;			
			break;
		case 2: *lspd_val = -64; //64
			*rspd_val = 64; //128
			*dir_val = 1;
			a_key = true;			
			break;
		case 3: *lspd_val = 64;
			*rspd_val = 64;
			*dir_val = -1; 
			s_key = true;			
			break;
		case 4: *lspd_val = 64;
			*rspd_val = -64;
			*dir_val = 1; 
			d_key = true;			
			break;
	}
}


int v1 = 0;
int v2 = 0;

ros::Publisher pub_1, pub_2, pub_3, pub_4;

std_msgs::Int16 lspd_value, rspd_value, dir_value, dur_value;
int a,b,c,d;

void key_call(int key_pressed_val)
{
	a=lspd_value.data;
	b=rspd_value.data;
	c=dir_value.data;
	d=dur_value.data;
	assignValue(key_pressed_val, &a, &b, &c, &d);
	lspd_value.data = a;
	rspd_value.data = b;
	dir_value.data = c;
	dur_value.data = d;
	ROS_INFO("Key pressed call");
	ROS_INFO("Key: [%d]\n", key_pressed_val);
	pub_1.publish (lspd_value);
	pub_2.publish (rspd_value);
	pub_3.publish (dir_value);
	pub_4.publish (dur_value);
}

void downCallBack(const std_msgs::Int16::ConstPtr& keyno)
{
	v1=keyno->data;
	if (v1 == 0) {
		return;
	}
	a=lspd_value.data;
	b=rspd_value.data;
	c=dir_value.data;
	d=dur_value.data;
	assignValue(v1, &a, &b, &c, &d);
	lspd_value.data = a;
	rspd_value.data = b;
	dir_value.data = c;
	dur_value.data = d;
	pub_1.publish (lspd_value);
	ROS_INFO("Lspeed: [%d]\n", a);
	pub_2.publish (rspd_value);
	ROS_INFO("Rspeed: [%d]\n", b);
	pub_3.publish (dir_value);
	ROS_INFO("Direction: [%d]\n", c);
	pub_4.publish (dur_value);
	ROS_INFO("Duration: [%d]\n", d);
}

void upCallBack(const std_msgs::Int16::ConstPtr& keyno)
{
	lspd_value.data=0; rspd_value.data=0; dir_value.data=1; dur_value.data=10;	
	v2=keyno->data;
	switch(v2){
		case 1: w_key = false;			
			break;
		case 2: a_key = false;			
			break;
		case 3: s_key = false;			
			break;
		case 4: d_key = false;			
			break;
	}
	ROS_INFO("Keyup: [%d]\n", v2);
	pub_1.publish (lspd_value);
	ROS_INFO("Lspeed: [%d]\n", lspd_value.data);
	pub_2.publish (rspd_value);
	ROS_INFO("Rspeed: [%d]\n",rspd_value.data);
	pub_3.publish (dir_value);
	ROS_INFO("Direction: [%d]\n", dir_value.data);
	pub_4.publish (dur_value);
	ROS_INFO("Duration: [%d]\n", dur_value.data);
}

int main (int argc, char **argv)
{
	ros::init(argc, argv, "keyboard_subscriber");
	ros::NodeHandle nh;
	pub_1 = nh.advertise<std_msgs::Int16>("lspd", 100);
	pub_2 = nh.advertise<std_msgs::Int16>("rspd", 100);
	pub_3 = nh.advertise<std_msgs::Int16>("dir", 100);
	pub_4 = nh.advertise<std_msgs::Int16>("dur", 100);
	ROS_INFO("Initialized!\n");
	ros::Subscriber sub1 = nh.subscribe("keydown_pub", 100, &downCallBack);
	ros::Subscriber sub2 = nh.subscribe("keyup_pub", 100, &upCallBack);
	while(ros::ok()) {
		ros::spinOnce();
		std::this_thread::sleep_for (std::chrono::milliseconds(8));
		if (w_key == true) {
			key_call(1);
		}
		else if (a_key == true) {
			key_call(2);
		}
		else if (s_key == true) {
			key_call(3);
		}
		else if (d_key == true) {
			key_call(4);
		}
	}
	return 0;
}
	

