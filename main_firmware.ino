#include <Console.h> //YUN-i "Serial Monitor"
#include <NewPing.h> //Ultrasonic sensor's library
#define SONAR_NUM 4      // Number of sensors, syntax from NewPing
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping, syntax from NewPing

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing (8, 9, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing (8, 10, MAX_DISTANCE), //THEY CAN ALL WORK WITH ONE PIN ONLY, MAYBE WE HAVE TO DO IT BECAUSE WE NEED 2 DIGITAL PINS FOR A COMPASS
  NewPing (8, 11, MAX_DISTANCE),
  NewPing (8, 12, MAX_DISTANCE)
};

//motors
const int motor1 = 5; //left PWM 10%-90% (0-5220rpm reductor 7:1)
const int motor2 = 6; //right PWM 10%-90% (0-5220rpm reductor 7:1)
const int motorDir1 = 4; //left LOW-CW HIGH-CCW
const int motorDir2 = 7; //right LOW-CW HIGH-CCW
const int enable = 13; //motors enable pin HIGH-enabled
int speed = 40; //PWM value 26-229

//interrupts
const byte interrupt0 = 3; //left motor's Hall sensor to IRQ
volatile unsigned long firstPulseTime0; //not needed I guess
volatile unsigned long lastPulseTime0; //not needed I guess
volatile unsigned long numPulses0; //counter for pulses
const byte interrupt1 = 2; //right motor's Hall sensor to IRQ
volatile unsigned long firstPulseTime1; //not needed I guess
volatile unsigned long lastPulseTime1; //not needed I guess
volatile unsigned long numPulses1; //counter for pulses

void setup() {
  Bridge.begin(); // Serial bridge 32u4<->AR9331 THIS IS WHY ROBOT WON'T MOVE BEFORE OPENWRT HAS BOOTED, and we need it to get the WIFI Serial Monitor
  Console.begin(); // Open WIFI serial monitor  
  pinMode(interrupt0, INPUT); //enable interrupts
  pinMode(interrupt1, INPUT); //enable interrupts
  attachInterrupt(digitalPinToInterrupt(interrupt0), isr0, FALLING); //interrupt behaviour (pin, function_to_call, rising or falling edge)
  attachInterrupt(digitalPinToInterrupt(interrupt1), isr1, FALLING); //interrupt behaviour
  digitalWrite(enable, LOW); //disable motor drivers, basically a safety feature
//  analogWrite(motor1, 26); //disable motor drivers (unnecessary?)
//  analogWrite(motor2, 26); //disable motor drivers (unnecessary?)
//  delay(50); //maybe unnecessary, motor driver gave invalid PWM error...
}

void loop() {     
  do
{
    for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.    
  }  
  forwards();
  printInterrupts(); //print pulse counters
} while(sonar[0].ping_cm()>10)  ;
   stopp();
   delay(2000);
   
  if(sonar[0].ping_cm()<10){   
    do
{
    for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  }
  
  backwards();
//  Console.println(sonar[2].ping_cm());  
} while(sonar[2].ping_cm()>10);
}
stopp();
delay(2000);
}

void isr0() { //Interrupt Service Routine for left wheel
   unsigned long now0 = micros(); //in case we want to measure its speed
 if (numPulses0 == 1) //in case we want to measure its speed
 {
   firstPulseTime0 = now0; //in case we want to measure its speed
 }
 else //in case we want to measure its speed
 {
   lastPulseTime0 = now0; //in case we want to measure its speed
 }
 ++numPulses0;
//   Console.print("Left:");
//  Console.print(numPulses0);
}

void isr1() { //Interrupt Service Routine for left wheel
 unsigned long now1 = micros();
 if (numPulses1 == 1)
 {
   firstPulseTime1 = now1;
 }
 else
 {
   lastPulseTime1 = now1;
 }
 ++numPulses1;
// Console.print("Right:");
// Console.print(numPulses1);
}


void forwards(){  
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  delay(10);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
  delay(10);
  digitalWrite(enable, HIGH);
}

void backwards(){ 
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  delay(10);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
  delay(10);
  digitalWrite(enable, HIGH);
}

void left(){
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  delay(10);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, HIGH);
  delay(10);
  int leftState = numPulses0;
  int rightState = numPulses1;
  while(numPulses0 < leftState + 25){
    digitalWrite(enable, HIGH);
    }  
  digitalWrite(enable, LOW);
}

void right(){
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  delay(10);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, LOW);
  delay(10);
  int leftState = numPulses0;
  int rightState = numPulses1;
  while(numPulses0 < leftState + 25){
    digitalWrite(enable, HIGH);
    }  
  digitalWrite(enable, LOW);
}

void stopp(){  
  analogWrite(motor1, 26);
  analogWrite(motor2, 26);
  delay(10);
  digitalWrite(enable, LOW);
}

void printAllSensors(){ //this doesn't work this way beacause 'i' is defined at the beginning of loop where we ping the sensors
//  Console.print(i);
//    Console.print("=");
//    Console.print(sonar[i].ping_cm());
//    Console.print("cm ");
//    Console.println();
}

void printInterrupts(){
  Console.print("Left:");
  Console.print(numPulses0);
  Console.print("Right:");
  Console.print(numPulses1);
  Console.println();
}

