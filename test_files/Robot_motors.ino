#include <Console.h>

//L293D
//Motor A
const int motorPin1  = 6;  // Pin 14 of L293
const int motorPin2  = 9;  // Pin 10 of L293
//Motor B
const int motorPin3  = 10; // Pin  7 of L293
const int motorPin4  = 11;  // Pin  2 of L293
//HC-SR04
const int leftTrigPin = 3;
const int leftEchoPin = 5;
const int frontTrigPin = 2;
const int frontEchoPin = 4;
const int rightTrigPin = 11;
const int rightEchoPin = 12;

long leftDuration;
long frontDuration;
long rightDuration;

int leftDistance;
int frontDistance;
int rightDistance;

int speed = 100;

//This will run only one time.
void setup(){

  Bridge.begin();
  Console.begin(); 

  while (!Console){
    ; // wait for Console port to connect.
  }
  Console.println("You're connected to the Console!!!!");
 
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(frontTrigPin, OUTPUT); // Sets the backTrigPin as an Output
    pinMode(frontEchoPin, INPUT); // Sets the backEchoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
}
    //This code  will turn Motor A clockwise for 2 sec. forward
void forward(){
    analogWrite(motorPin1, speed);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, speed);
    analogWrite(motorPin4, 0);
    delay(500); 
    }
    //This code will turn Motor A counter-clockwise for 2 sec. backwards
void backwards(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, speed+5);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, speed);
    //delay(5000);
    }
    //This code will turn Motor B clockwise for 2 sec. right
void right(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, speed);
    analogWrite(motorPin3, speed);
    analogWrite(motorPin4, 0);
    //delay(5000); 
    }
    //This code will turn Motor B counter-clockwise for 2 sec.left
void left(){
    analogWrite(motorPin1, speed);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, speed);
    delay(1000);    
    }
    //And this code will stop motors
void stopp(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  }
int leftSensor(){
    // Clears the TrigPin
    digitalWrite(leftTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the TrigPin on HIGH state for 10 micro seconds
    digitalWrite(leftTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(leftTrigPin, LOW);
    // Reads the EchoPin, returns the sound wave travel time in microseconds
    leftDuration = pulseIn(leftEchoPin, HIGH);
    // Calculating the distance
    leftDistance= leftDuration*0.034/2;
    // Prints the distance on the Serial Monitor
    Console.print("Distance in left: ");
    Console.println(leftDistance);
    return leftDistance;
  }
int frontSensor(){
    // Clears the backTrigPin
    digitalWrite(frontTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the backTrigPin on HIGH state for 10 micro seconds
    digitalWrite(frontTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontTrigPin, LOW);
    // Reads the backEchoPin, returns the sound wave travel time in microseconds
    frontDuration = pulseIn(frontEchoPin, HIGH);
    // Calculating the distance
    frontDistance= frontDuration*0.034/2;
    // Prints the distance on the Serial Monitor
    Console.print("Distance in back: ");
    Console.println(frontDistance);
    return frontDistance;
  }
int rightSensor(){
    // Clears the TrigPin
    digitalWrite(rightTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the TrigPin on HIGH state for 10 micro seconds
    digitalWrite(rightTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(rightTrigPin, LOW);
    // Reads the EchoPin, returns the sound wave travel time in microseconds
    rightDuration = pulseIn(rightEchoPin, HIGH);
    // Calculating the distance
    rightDistance= rightDuration*0.034/2;
    // Prints the distance on the Serial Monitor
    Console.print("Distance in right: ");
    Console.println(rightDistance);
    return rightDistance;
  }


void turnLeft(){
    digitalWrite(frontTrigPin, LOW);
    digitalWrite(leftTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(frontTrigPin, HIGH);
    digitalWrite(leftTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontTrigPin, LOW);
    digitalWrite(leftTrigPin, LOW);
    frontDuration = pulseIn(frontEchoPin, HIGH);
    leftDuration = pulseIn(leftEchoPin, HIGH);
    frontDistance = frontDuration*0.034/2;
    leftDistance = leftDuration*0.034/2;
    Console.print("Distance in front: ");
    Console.println(frontDistance);
    Console.print("Distance in left: ");
    Console.println(leftDistance);
    
    //return backDistance;
  }

void loop(){
  do{
    frontSensor();
    backwards();    
    }
  while(frontDistance > 5);
  stopp();
  //if ()
  do{
    turnLeft();
    right();
    }
  while(leftDistance < 5 && frontDistance < 20);
  stopp();
/*
  do{
    frontSensor();
    backwards();    
    }
  while(frontDistance > 5);
  stopp();
  do{
    left();
    rightSensor();    
    }
  while(rightDistance > 5);
  stopp();
*/  
 /* do{
    frontSensor();
    forward();
  }
 while (frontDistance > 5);
 stopp();
 */
}

