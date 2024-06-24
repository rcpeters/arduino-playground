/* 
* Water pump plus capacitive soil sensor, Put together via following 
* tuturials
*
* https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/components_basic/28-component_pump.html
* 
* https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/components_basic/10-component_soil.html
*
*/

/*
  This program reads the analog input from a capacitive soil moisture sensor 
  connected to pin A0 and prints the value to the serial monitor. 
  The smaller the value, the higher the soil moisture level. 
  Board: Arduino 
  Component: Capacitive soil moisture sensor
*/

/*
  This code defines and initializes two pins for a centrifugal pump and sets 
  the speed of one of the pump pins to HIGH and the other to LOW, causing the 
  pump to spin in one direction.  
  Board: Arduino
  Component: Motor and L9110 motor control board
*/

const long inWater = 2800;  // this will change for each sensor
const long outOfWater = 3200;
const long inMiddle = outOfWater - ((outOfWater - inWater) / 2);
const long pumpInterval = 1000;  // how long to pump water for when we read dry

// Define the pump pins
const int motorB_1A = 9;
const int motorB_2A = 10;

// Define the sensor pin
const int sensorPin = A0;

void pumpFor(long mills) {
  digitalWrite(motorB_1A, HIGH);
  digitalWrite(motorB_2A, LOW);

  delay(mills);  // delay

  digitalWrite(motorB_1A, LOW);  // turn off the pump
  digitalWrite(motorB_2A, LOW);
}

void setup() {

  pinMode(motorB_1A, OUTPUT);  // set pump pin 1 as output
  pinMode(motorB_2A, OUTPUT);  // set pump pin 2 as output

  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate
}

void loop() {
  long sensorRead = analogRead(A0);
  Serial.println(analogRead(A0));  // The smaller the value, the higher the soil moisture level
  if (sensorRead > inMiddle)
    pumpFor(pumpInterval);
  delay(500);  // Wait for 500 milliseconds before taking the next reading
}