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
#include <Kinematics.h> //converts linear x and angular z to left and right rotation speeds

//Arduino pin Setup
#define L_PWM 11
#define L_DIR 12
#define R_PWM 9
#define R_DIR 8
#define LED_PIN 13

//Kinematics Variables
#define LR_WHEEL_DISTANCE 0.242  //meters, center to center
#define MAX_MOTOR_RPM 560 //560 under max load, 617 no load
#define PWM_BITS 8  //set for Arduino Uno and Mega
#define WHEEL_DIAMETER 0.048 //meters from trough between teeth across center to trough between teeth
#define FR_WHEEL_DISTANCE 0 //considered to be a 2 wheeled robot

//System Variables
#define MAX_PWM_WRITE 255 //max value to use with PWM analogWrite function
#define LEFT_FWD false  //reversed due to construction
#define RIGHT_FWD true

//Placeholders
float linear_vel = 0.000; //init at 0, positive is forward m/s
float angular_vel = 0.000; //init at 0, positive is CCW m/s
bool twistCb_flag = false;

//ROS Defines ----------------------------------------------------------------------
void twistCallback(const geometry_msgs::Twist& drive_vel) {
  linear_vel = drive_vel.linear.x;
  angular_vel = drive_vel.angular.z;

  twistCb_flag = true;
  
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); //test - toggle when ran
}

ros::NodeHandle nh; //create node handle for local use
ros::Subscriber<geometry_msgs::Twist> sub_velocity("cmd_vel", twistCallback); //create subscriber to cmd_vel

// Kinematic Defines ---------------------------------------------------------------
Kinematics motors(MAX_MOTOR_RPM, WHEEL_DIAMETER, FR_WHEEL_DISTANCE, LR_WHEEL_DISTANCE, PWM_BITS);

//Functions ------------------------------------------------------------------------
void motor_write(int left_PWM, int right_PWM)  {
  //Get motor's directions
  bool left_dir;
  if(left_PWM >= 0) left_dir = LEFT_FWD;
  else left_dir = !LEFT_FWD;

  bool right_dir;
  if(right_PWM >= 0) right_dir = RIGHT_FWD;
  else right_dir = !RIGHT_FWD;

  //Write the speed to the motors
  digitalWrite(L_DIR, left_dir);
  analogWrite(L_PWM, abs(left_PWM));
  digitalWrite(R_DIR, right_dir);
  analogWrite(R_PWM, abs(right_PWM));
}

//Setup ----------------------------------------------------------------------------
void setup() {
  //Set up test led
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
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
    //get motor speed
    Kinematics::output motor_rpm;
    motor_rpm = motors.getRPM(linear_vel, 0, angular_vel);  //robot cannot move in the y direction.
    int left_pwm = map(motor_rpm.motor1, -MAX_MOTOR_RPM, MAX_MOTOR_RPM, -MAX_PWM_WRITE, MAX_PWM_WRITE);
    int right_pwm = map(motor_rpm.motor2, -MAX_MOTOR_RPM, MAX_MOTOR_RPM, -MAX_PWM_WRITE, MAX_PWM_WRITE);
    motor_write(left_pwm, right_pwm);
  
    twistCb_flag = false; //reset flag
  }
  
  //run each loop
  nh.spinOnce();
  delay(50);
}
