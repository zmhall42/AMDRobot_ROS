/*
 * Test read cmd vel topic
 * AMDRobot-ROS Project
 * Created: 2021-10-25
 * Author(s): TTU Spring 2021 - Fall 2021 ECE Team 
 */
// Libraries
#include <ros.h>
#include <geometry_msgs/Twist.h>
//#include <std_msgs/Float32MultiArray.h>

//bool callbackRan = false; //true when callback is run
const int ledPin = 13;  //pin 13 to signal when callback has run
int demand_x = 0;
int demand_z = 0;

// ROS Setup -----------------------------------------------------------------------
ros::NodeHandle nh; //create ROS Node

// Subscriber setup
void twistCallback(const geometry_msgs::Twist& twist_msg) {
  demand_x = twist_msg.linear.x;
  demand_z = twist_msg.angular.z;
  //callbackRan = true;

  digitalWrite(ledPin, !digitalRead(ledPin)); //toggle led on pin 13
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", twistCallback);  //create subscriber

// Publisher Setup
//std_msgs::Float32MultiArray read_vals;
//ros::Publisher echo_vals("echo_vals", &read_vals);

// Setup ---------------------------------------------------------------------------
void setup() {
  nh.initNode();
  //nh.advertise(echo_vals);
  nh.subscribe(sub);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

// Main Loop -----------------------------------------------------------------------
void loop() {
  //if(callbackRan) {
    //save data to echo
    
    
  //  echo_vals.publish(&read_vals);  //publish read_vals
  //  callbackRan = false;  //reset flag
  //}
  nh.spinOnce();
  delay(50);
}
