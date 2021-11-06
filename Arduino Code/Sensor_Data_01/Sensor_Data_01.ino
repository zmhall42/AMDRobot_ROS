/*
 * Read all sensor data and publish to /sensor_data topic
 * AMDRobot-ROS Project
 * Created: 2021-11-06
 * Author(s): TTU Spring 2021 - Fall 2021 ECE Team 
 * 
 * Wiring:
 * Mega:
 *    Pin ## = 
 *    Pin ## = 
 */

//Includes -------------------------------------------------------------------------
#include <ros.h> //All ROS functionality
/* Be sure to change \libraries\Rosserial_Arduino_Library\src\ros\msg.h:
 *     line 40 from cstring to string.h
 *     line 68 from std::memcpy to memcpy
 *     line 182 from std::memcpy to memcpy
 */

//Mega Pin Setup
//#define Pin_name ##

// ROS Setup -----------------------------------------------------------------------
ros::NodeHandle nh; //create ROS Node


// Setup ---------------------------------------------------------------------------
void setup() {
  nh.initNode();
  nh.advertise(sensor_data);

  //Pin Setup
}

// Main Loop -----------------------------------------------------------------------
void loop() {
  //Do thing
  nh.spinOnce();
  delay(50);
}
