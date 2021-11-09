

#define echoPin1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin1 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin2 4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin2 5 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin3 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin3 7 //attach pin D3 Arduino to pin Trig of HC-SR04
#define echoPin4 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin4 9 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement
long duration3; // variable for the duration of sound wave travel
int distance3; // variable for the distance measurement
long duration4; // variable for the duration of sound wave travel
int distance4; // variable for the distance measurement

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigPin4, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin4, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed


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
  // Displays the distance on the Serial Monitor
   // Clears the trigPin condition
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration4 = pulseIn(echoPin4, HIGH);
  // Calculating the distance
  distance4 = duration4 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance1 Distance2 Distance3 Distance4");
  
  Serial.println();
  Serial.print(distance1);
  Serial.print(" cm    ");
  Serial.print(distance2);
  Serial.print(" cm    ");
  Serial.print(distance3);
  Serial.print(" cm    ");
  Serial.print(distance4);
  Serial.print(" cm    ");
  Serial.println();
  delay(500);

  
}
