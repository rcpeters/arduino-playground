/* 
 * ARDUINO TRAFFIC LIGHT WITH TOUCH SENSOR and OLED SCREEN
 * Silly little game for Lucy.
 *
 * Variation of Red light Green light game.
 * Press the button to start. You are given 10 second to walk away from the 
 * button to a starting point you designate (10 ro 30 ft). After which the
 * lights change colors. On green you move closer to the button and Red you stop.
 * First one to reach and touch the button wins.
 *
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

typedef enum {
  RUN = 0,
  STOP = 1,
  INIT = 2,
} GAMESTATE;

int RED = 9;     // PIN for LED
int YELLOW = 8;  // PIN for LED
int GREEN = 7;   // PIN for LED
int currentColor = YELLOW;
bool runGame = false;

const int TOUCH_PIN = 6;  // PIN for touch sensor
int touchState = LOW;
int gameState = STOP;
long started = 0;
long colorChange = 0;
long colorChangeDuration = 0;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  Serial.begin(9600);         // Begin serial communication
  pinMode(TOUCH_PIN, INPUT);  // Sets the pinmode to input
  nextColor();

  stopGame();
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
    setText("Go");
  } else if (currentColor == GREEN) {
    currentColor = YELLOW;
    setText("Warning");
  } else {
    currentColor = RED;
    setText("Stop");
  }
  digitalWrite(currentColor, HIGH);
  Serial.println(currentColor);
}

void stopGame() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, HIGH);
  setText("PRESS to\n START");
  gameState = STOP;
  started = 0;
}

void youWin() {
  long winTime = millis();
  setText("YOU WIN\n !!!!!!!!");
  while (winTime + 3000 > millis()) {
    digitalWrite(RED, LOW);
    delay(100);
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    delay(100);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, HIGH);
    delay(100);
    digitalWrite(GREEN, LOW);
  }
  stopGame();
}

void startGame() {
  digitalWrite(RED, HIGH);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  setText("Go to \nSTART!!! 10");
  started = millis();
  gameState = RUN;
}

void changeGameState() {
  if (gameState == STOP)
    startGame();
  else
    youWin();
}

// gives 10 seconds to go other start 
bool preStart() {
  return started != 0 && started + 10000 > millis();
}

void loop() {
  int newTouchState = digitalRead(TOUCH_PIN);
  if (touchState == LOW && newTouchState == HIGH) {
    Serial.println("The sensor is touched");
    if (!preStart()) {
      changeGameState();
    }
  }
  // save the the last state
  touchState = newTouchState;

  if (preStart()) {
    setText("Go to \nSTART!!!");
    if (millis() % 500 > 250) {
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, HIGH);
    } else {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    }
  } else if (colorChange < started) {
    if (colorChangeDuration < millis()) {
      if (currentColor == GREEN)  //make yellow always fast
        colorChangeDuration = millis() + 250;
      else
        colorChangeDuration = millis() + random(500, 4000);
      nextColor();
    }
  }
}