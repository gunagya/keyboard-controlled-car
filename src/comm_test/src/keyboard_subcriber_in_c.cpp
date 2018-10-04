#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Int16.h"

void assignValue (int keycode, int* lspd_val, int* rspd_val, int* dir_val, int* dur_val)
{
	*dur_val=10;
	switch (keycode)
	{
		case 1: *lspd_val = 128;
			*rspd_val = 128;
			*dir_val = 1; break;
		case 2: *lspd_val = 64;
			*rspd_val = 128;
			*dir_val = 1; break;
		case 3: *lspd_val = 128;
			*rspd_val = 128;
			*dir_val = -1; break;
		case 4: *lspd_val = 128;
			*rspd_val = 64;
			*dir_val = 1; break;
	}
}


int v1 = 0;
int v2 = 0;

ros::Publisher pub_1, pub_2, pub_3, pub_4;

std_msgs::Int16 lspd_value, rspd_value, dir_value, dur_value;
int a,b,c,d;

void downCallBack(const std_msgs::Int16::ConstPtr& keyno)
{
	v1=keyno->data;
	a=lspd_value.data;
	b=rspd_value.data;
	c=dir_value.data;
	d=dur_value.data;
	assignValue(v1, &a, &b, &c, &d);
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
	lspd_value.data=0; rspd_value.data=0; dir_value.data=0; dur_value.data=10;	
	v2=keyno->data;
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
	ros::spin();
	return 0;
}
	

