#include "ros/ros.h"	//Include all necessary header files so it will work with ROS
#include "std_msgs/String.h"	//Include String message from std_msgs package
#include <sstream>
#include "geometry_msgs/Twist.h"    //Include Twist message from geometry_msgs package
#include <wiringPi.h>

using namespace std;
//Variables
const int i_leftPWMPin = 18;    //GPIO18 is PWM Pin
const int i_leftDIRPin = 16;    //GPIO16 is DIR Pin
const int i_rightPWMPin = 12;   //GPIO12 is PWM Pin
const int i_rightDIRPin = 5;    //GPIO05 is DIR Pin


//Setup functions
void vfn_pinSetup()    {
    pinMode(i_leftPWMPin, OUTPUT);
    pinMode(i_leftDIRPin, OUTPUT);
    pinMode(i_rightPWMPin, OUTPUT);
    pinMode(i_rightDIRPin, OUTPUT);
}

void vfn_baseCmdVel(const stdmsgs::String::ConstPtr& msg)  {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void vfn_rosSetup(int argc, char** argv) {
    ros::init(argc, argv, "chassis_test01");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("base_cmd_vel", 10, vfn_baseCmdVel);	//Subscribe in master to a topic called base_cmd_vel. Save 10 messages in buffer before deleting old messages.  Run above function when a message arrives
}

//Main loop
int main(int argc, char** argv)  {
    vfn_pinSetup(); //setup all pins
    vfn_rosSetup(argc, argv);   //setup ROS stuff

    //loop
    while(1)    {
        
    }
    return 0;
}