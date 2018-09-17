#include <ros.h>
#include <std_msgs/Int16.h>

int min=1;
int max=256;
int rand_no;


ros::NodeHandle nh;
std_msgs::Int16 rand_msg;
ros::Publisher pub_1("/random_number1", &rand_msg);
ros::Publisher pub_2("/random_number2", &rand_msg);
ros::Publisher pub_3("/random_number3", &rand_msg);
ros::Publisher pub_4("/random_number4", &rand_msg);

int random_number(){
  rand_no= random(min, max);
  return rand_no;
}

 
void setup() {
   nh.initNode();
   nh.advertise(pub_1);
   nh.advertise(pub_2);
   nh.advertise(pub_3);
   nh.advertise(pub_4);
}


void loop() {
  rand_msg.data = random_number();
  pub_1.publish(&rand_msg);
  rand_msg.data = random_number();
  pub_2.publish(&rand_msg);
  rand_msg.data = random_number();
  pub_3.publish(&rand_msg);
  rand_msg.data = random_number();
  pub_4.publish(&rand_msg);
  nh.spinOnce();
  delay(1000);
 }
