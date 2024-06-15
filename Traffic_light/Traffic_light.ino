/* 
 * ARDUINO TRAFFIC LIGHT WITH TOUCH SENSOR
 * Silly little project for Lucy.
 * You can visit 
 * https://projecthub.arduino.cc/krishna_agarwal/traffic-light-using-arduino-a-beginner-project-35f8c6
 * and
 * https://arduinogetstarted.com/tutorials/arduino-touch-sensor
 * for a more detailed writeup.
 */

int RED = 9; // PIN for LED
int YELLOW = 8; // PIN for LED
int GREEN = 7; // PIN for LED
int currentColor = YELLOW; 

const int TOUCH_PIN = 6; // PIN for touch sensor
int touchState = LOW;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  Serial.begin(9600);         // Begin serial communication
  pinMode(TOUCH_PIN, INPUT);  // Sets the pinmode to input
  nextColor();
}

void nextColor() {
  digitalWrite(currentColor, LOW);
  if (currentColor == RED) currentColor = GREEN;
  else if (currentColor == GREEN) currentColor = YELLOW;
  else currentColor = RED;
  digitalWrite(currentColor, HIGH);
  Serial.println(currentColor);
}

void loop() {
  int newTouchState = digitalRead(TOUCH_PIN);

  if (touchState == LOW && newTouchState == HIGH) {
    Serial.println("The sensor is touched");
    nextColor();
  }
  // save the the last state
  touchState = newTouchState;
}
