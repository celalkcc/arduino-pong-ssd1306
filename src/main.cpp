#include <Arduino.h>



//SSD1306 Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>


// Initializing the Display
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// defining the Playing field
const int UPPER_BORDER = 0;
const int LOWER_BORDER = (SCREEN_HEIGHT - 1); // Using Screenheight and width, to make it portable to other displays
const int LEFT_BORDER = 0;
const int RIGHT_BORDER = (SCREEN_WIDTH - 1);

// defining Poti Pins
const int potiLeftPlayer = A0;
const int potiRightPlayer = A1;
const int button = 4;

enum machineState {
  START_SCREEN,
  START_TIMER,
  IN_GAME,
  LEFT_WINS,
  RIGHT_WINS,
};

machineState currentState = START_SCREEN; 
static unsigned long timerMillis = 0;
// header Files
#include "playerManagement.h"
#include "ballManagement.h"
#include "rendering.h"
#include "start.h"
#include "pointsManagement.h"
/****************************************/
// Main Program
/****************************************/

void setup() {
  Serial.begin(9600); // Initializing Logging
  Serial.println("Firmware Version 0.99\n");

  pinMode(button, INPUT_PULLUP);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay(); 
  millis();
}


void loop(){
  
  switch(currentState) {

    case START_SCREEN:
      static unsigned long menuMillis = 0;
      static bool picSelector = 0;
      if (millis() - menuMillis > 2000) {
        picSelector = !picSelector;
        menuMillis = millis();
      }
      printStartScreen(picSelector);

      if(!digitalRead(button)) {
        timerMillis = millis();
        ballInCenter();
        currentState = START_TIMER;
      }
      break;

    case START_TIMER:

      updatePlayers();
      renderScreen();
      if(millis() -timerMillis > 2000) {
        currentState = IN_GAME;
      }
      break;

    case IN_GAME:
      updatePlayers();
      borderCheck();
      directionFlip();
      renderScreen();
      checkPoints();
      break;

    case LEFT_WINS:
      display.clearDisplay();
      display.drawBitmap(0, 0, leftWins, 128, 32, WHITE);
      display.display();
      delay(4000);
      currentState = START_SCREEN;
      break;

    case RIGHT_WINS:
      display.clearDisplay();
      display.drawBitmap(0, 0, rightWins, 128, 32, WHITE);
      display.display();
      delay(4000);
      currentState = START_SCREEN;
      break;
      currentState = START_SCREEN;
  }
}


