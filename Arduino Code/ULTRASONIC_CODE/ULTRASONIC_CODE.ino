#include <ros.h>
#include <std_msgs/UInt16MultiArray.h>


#define echoPin1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 5 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin3 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin3 7 //attach pin D3 Arduino to pin Trig of HC-SR04

const int pingPin1 = 8;
const int pingPin2 = 9;

// defines variables
long duration1; // variable for the duration of sound wave travel
unsigned int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
unsigned int distance2; // variable for the distance measurement
long duration3; // variable for the duration of sound wave travel
unsigned int distance3; // variable for the distance measurement

long duration4, duration5;
unsigned int distance4, distance5;




ros::NodeHandle nh;
std_msgs::UInt16MultiArray Sensors;
ros::Publisher pub_Sensors("/sensor_values",&Sensors);




void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
 
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    Sensors.layout.dim = (std_msgs::MultiArrayDimension *) malloc(sizeof(std_msgs::MultiArrayDimension)*2);
    Sensors.layout.dim[0].label = "sensors";
    Sensors.layout.dim[0].size = 5;
    Sensors.layout.dim[0].stride = 1;
    Sensors.layout.data_offset = 0;
    Sensors.data = (unsigned int *)malloc(sizeof(unsigned int)*8);
    Sensors.data_length = 5;
    nh.advertise(pub_Sensors);


}
void loop() {

   
    
  // Clears the trigPin condition
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Sensors.data[0] = distance1;
  // Displays the distance on the Serial Monitor
   // Clears the trigPin condition
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Sensors.data[1] = distance2;
  // Displays the distance on the Serial Monitor
   // Clears the trigPin condition
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Sensors.data[2] = distance3;
  // Displays the distance on the Serial Monitor
   // Clears the trigPin condition
pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin1, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin1, INPUT);
  duration4 = pulseIn(pingPin1, HIGH);

  // convert the time into a distance
  distance4 = microsecondsToCentimeters(duration4);
  Sensors.data[3] = distance4;
  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2, LOW);

  pinMode(pingPin2, INPUT);
  duration5 = pulseIn(pingPin2, HIGH);
  Sensors.data[4] = distance5;
  // convert the time into a distance
  distance5 = microsecondsToCentimeters(duration5);


 
//  Serial.print("Distance1 Distance2 Distance3 Distance4 Distance5");
//  
//  Serial.println();
//  Serial.print(distance1);
//  Serial.print(" cm    ");
//  Serial.print(distance2);
//  Serial.print(" cm    ");
//  Serial.print(distance3);
//  Serial.print(" cm    ");
//  Serial.print(distance4);
//  Serial.print(" cm    ");
//  Serial.print(distance5);
//  Serial.print(" cm    ");
//  Serial.println();
//  delay(500);

  pub_Sensors.publish(&Sensors);
  nh.spinOnce();
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
