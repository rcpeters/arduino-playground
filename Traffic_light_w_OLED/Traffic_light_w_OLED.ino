/* 
 * ARDUINO TRAFFIC LIGHT WITH TOUCH SENSOR and OLED SCREEN
 * Silly little project for Lucy.
 * You can visit 
 * https://projecthub.arduino.cc/krishna_agarwal/traffic-light-using-arduino-a-beginner-project-35f8c6
 * and
 * https://arduinogetstarted.com/tutorials/arduino-touch-sensor
 * for a more detailed writeup.
 */

/* Starting with Arduino OLED coding
 *  for " arduino oled i2c tutorial : 0.96" 128 X 32 for beginners"
 *  subscribe for more arduino Tuorials and Projects https://www.youtube.com/channel/UCM6rbuieQBBLFsxszWA85AQ?sub_confirmation=1
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int RED = 9;     // PIN for LED
int YELLOW = 8;  // PIN for LED
int GREEN = 7;   // PIN for LED
int currentColor = YELLOW;

const int TOUCH_PIN = 6;  // PIN for touch sensor
int touchState = LOW;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  Serial.begin(9600);         // Begin serial communication
  pinMode(TOUCH_PIN, INPUT);  // Sets the pinmode to input
  nextColor();
}

void setText(char* text) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(text);
  display.display();
}

void nextColor() {
  digitalWrite(currentColor, LOW);
  if (currentColor == RED) {
    currentColor = GREEN;
    setText("Go Go\nHeidi");
  } else if (currentColor == GREEN) {
    currentColor = YELLOW;
    setText("Warning\nHeidi");
  } else {
    currentColor = RED;
    setText("Stop\nHeidi");
  }
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
