#include <Console.h>
#include <NewPing.h>

#define SONAR_NUM 4      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing (8, 9, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing (8, 10, MAX_DISTANCE), 
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

void setup() {
  Bridge.begin(); // Serial bridge 32u4<->AR9331
  Console.begin(); // Open WIFI serial monitor  
  digitalWrite(enable, LOW);
  delay(10);
}

void forwards(){  
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);
  digitalWrite(enable, HIGH);
}

void backwards(){ 
  analogWrite(motor1, speed);
  analogWrite(motor2, speed);
  digitalWrite(motorDir1, LOW);
  digitalWrite(motorDir2, HIGH);
  digitalWrite(enable, HIGH);
}

void stopp(){  
  analogWrite(motor1, 26);
  analogWrite(motor2, 26);
  digitalWrite(enable, LOW);
}

void loop() { 
  do
{
    for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Console.print(i);
    Console.print("=");
    Console.print(sonar[i].ping_cm());
    Console.print("cm ");
  }
  Console.println();
  forwards();
} while(sonar[0].ping_cm()>10)  ;
   
  if(sonar[0].ping_cm()<10){
   
    do
{
    for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Console.print(i);
    Console.print("=");
    Console.print(sonar[i].ping_cm());
    Console.print("cm ");
  }
  Console.println();
  backwards();
} while(sonar[2].ping_cm()>10);
}
}

