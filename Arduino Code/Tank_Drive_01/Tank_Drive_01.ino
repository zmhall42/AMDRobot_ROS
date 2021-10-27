/*
 * Output drive from cmd_vel topic
 * AMDRobot-ROS Project
 * Created: 2021-10-26
 * Author(s): TTU Spring 2021 - Fall 2021 ECE Team 
 * 
 * Wiring:
 * Uno:
 *    Pin 11 = Left MD10C V3 PWM - PWM
 *    Pin 12 = Left MD10C V3 DIR - No PWM (HIGH/LOW)
 *    Pin 9 = Right MD10C V3 PWM - PWM
 *    Pin 8 = Right MD10C V3 DIR - No PWM (HIGH/LOW)
 */
//Includes -------------------------------------------------------------------------
#include <ros.h> //All ROS functionality
/* Be sure to change \libraries\Rosserial_Arduino_Library\src\ros\msg.h:
 *     line 40 from cstring to string.h
 *     line 68 from std::memcpy to memcpy
 *     line 182 from std::memcpy to memcpy
 */
#include <geometry_msgs/Twist.h>  //Use for drive message read

//Arduino pin Setup
#define L_PWM 11
#define L_DIR 12
#define R_PWM 9
#define R_DIR 8

//Variables
int linear_vel = 0; //init at 0, positive is forward
int angular_vel = 0; //init at 0, positive is CCW
const float dist_between_wheels = 0.1; //in m, center to center
const int max_speed_each_side = 1; //in m/s
bool twistCb_flag = false;

//ROS Defines ----------------------------------------------------------------------
void twistCallback(const geometry_msgs::Twist& drive_vel) {
  linear_vel = drive_vel.linear.x;
  angular_vel = drive_vel.angular.z;

  twistCb_flag = true;
}

ros::NodeHandle nh; //create node handle for local use
ros::Subscriber<geometry_msgs::Twist> sub_velocity("cmd_vel", twistCallback); //create subscriber to cmd_vel

//Functions ------------------------------------------------------------------------
void motor_write(int linear, int angular)  {
  //convert linear and angular to per motor speed --> motor = linear + (angular*dist between tracks)/2
  int left_vel = linear + (angular*dist_between_wheels)/2;  //If turn is backwards, change the +/- for this and next line
  int right_vel = linear - (angular*dist_between_wheels)/2;

  //set to max if too large (pos or neg)
  if(left_vel > max_speed_each_side) left_vel = max_speed_each_side;
  else if(left_vel < -max_speed_each_side) left_vel = -max_speed_each_side;
  
  if(right_vel > max_speed_each_side) right_vel = max_speed_each_side;
  else if(right_vel < -max_speed_each_side) right_vel = -max_speed_each_side;

  //adjust - scale each speed to the PWM range of the motor drivers
  int left_vel_adj = map(left_vel, -max_speed_each_side, max_speed_each_side, -255, 255); //255 is max PWM duty cycle
  int right_vel_adj = map(right_vel, -max_speed_each_side, max_speed_each_side, -255, 255);

  //left
  bool left_fwd;  //define direction variable
  int left_speed = abs(left_vel_adj); //set speed to the abs value of the adjusted velocity
  if(left_vel_adj > 0)  left_fwd = false; //if positive velocity, go forward
  else  left_fwd = true;  //otherwise, negative velocity and go backwards
  
  //right, same as left side above with opposite sign for direction
  bool right_fwd;
  int right_speed = abs(right_vel_adj);
  if(right_vel_adj > 0) right_fwd = true;
  else  right_fwd = false;

  //write the speed to the motors
  digitalWrite(L_DIR, left_fwd);
  analogWrite(L_PWM, left_speed);
  digitalWrite(R_DIR, right_fwd);
  analogWrite(R_PWM, right_speed);
}

//Setup ----------------------------------------------------------------------------
void setup() {
  //DIR Pin setup
  pinMode(L_DIR, OUTPUT); //set DIR pins to OUTPUTS
  pinMode(R_DIR, OUTPUT);
  digitalWrite(L_DIR, LOW); //start pins low
  digitalWrite(R_DIR, LOW);

  //PWM Pin setup
  pinMode(L_PWM, OUTPUT); //set PWM pins to OUTPUTS
  pinMode(R_PWM, OUTPUT);
  analogWrite(L_PWM, 0);  //start with motors at 0 velocity
  analogWrite(R_PWM, 0);

  //ROS Setup
  nh.initNode();  //turn on node
  nh.subscribe(sub_velocity); //subscribe to cmd_vel topic using sub_velocity specs
}

//Main Loop ------------------------------------------------------------------------
void loop() {
  if(twistCb_flag) {
    motor_write(linear_vel, angular_vel); //if twistCb run, change motor speed
    twistCb_flag = false;
  }

  //run each loop
  nh.spinOnce();
  delay(50);
}
