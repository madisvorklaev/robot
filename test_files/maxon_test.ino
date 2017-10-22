int enable = 4;
int motor = 5;

const byte interruptPin = 2;
volatile unsigned long firstPulseTime;
volatile unsigned long lastPulseTime;
volatile unsigned long numPulses;

void isr() {
   unsigned long now = micros();
 if (numPulses == 1)
 {
   firstPulseTime = now;
 }
 else
 {
   lastPulseTime = now;
 }
 ++numPulses;
}


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(enable, OUTPUT);
  pinMode(motor, OUTPUT); 
  digitalWrite(enable, HIGH);
  
  Serial.begin(19200);
  analogWrite(motor, 30);
}

float readFrequency(unsigned int sampleTime)
{
 numPulses = 0;                      // prime the system to start a new reading
 attachInterrupt(0, isr, RISING);    // enable the interrupt
 delay(sampleTime);
 detachInterrupt(0);
 return (numPulses < 3) ? 0 : (1000000.0 * (float)(numPulses - 2))/(float)(lastPulseTime - firstPulseTime);
}

// the loop function runs over and over again forever
void loop() {  
  float freq = readFrequency(1000);
 Serial.println(freq);
 delay(1000);
}


