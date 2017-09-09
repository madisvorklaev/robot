//L293D
//Motor A
const int motorPin1  = 6;  // Pin 14 of L293
const int motorPin2  = 7;  // Pin 10 of L293
//Motor B
const int motorPin3  = 8; // Pin  7 of L293
const int motorPin4  = 9;  // Pin  2 of L293
//HC-SR04
const int frontTrigPin = 2;
const int frontEchoPin = 4;
const int backTrigPin = 3;
const int backEchoPin = 5;
long frontDuration;
long backDuration;
int frontDistance;
int backDistance;

//This will run only one time.
void setup(){
 
    //Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(backTrigPin, OUTPUT); // Sets the backTrigPin as an Output
    pinMode(backEchoPin, INPUT); // Sets the backEchoPin as an Input
    Serial.begin(9600); // Starts the serial communication
    
    //Motor Control - Motor A: motorPin1,motorpin2 & Motor B: motorpin3,motorpin4
}
    //This code  will turn Motor A clockwise for 2 sec. forward
void forward(){
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);
    delay(500); 
    }
    //This code will turn Motor A counter-clockwise for 2 sec. backwards
void backwards(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);
    //delay(5000);
    }
    //This code will turn Motor B clockwise for 2 sec. right
void right(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);
    analogWrite(motorPin3, 180);
    analogWrite(motorPin4, 0);
    //delay(5000); 
    }
    //This code will turn Motor B counter-clockwise for 2 sec.left
void left(){
    analogWrite(motorPin1, 180);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);
    delay(200);    
    }
    //And this code will stop motors
void stopp(){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  }
int frontSensor(){
    // Clears the TrigPin
    digitalWrite(frontTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the TrigPin on HIGH state for 10 micro seconds
    digitalWrite(frontTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontTrigPin, LOW);
    // Reads the EchoPin, returns the sound wave travel time in microseconds
    frontDuration = pulseIn(frontEchoPin, HIGH);
    // Calculating the distance
    frontDistance= frontDuration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance in front: ");
    Serial.println(frontDistance);
    return frontDistance;
  }
int backSensor(){
    // Clears the backTrigPin
    digitalWrite(backTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the backTrigPin on HIGH state for 10 micro seconds
    digitalWrite(backTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(backTrigPin, LOW);
    // Reads the backEchoPin, returns the sound wave travel time in microseconds
    backDuration = pulseIn(backEchoPin, HIGH);
    // Calculating the distance
    backDistance= backDuration*0.034/2-3;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance in back: ");
    Serial.println(backDistance);
    return backDistance;
  }



void loop(){
  do{
    backSensor();
    backwards();    
    }
  while(backDistance > 5);
  stopp();
  forward();
  left();
  

}

