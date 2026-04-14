/*
MIT License
Copyright (c) 2026 Celal & Luis
*/
#include <Arduino.h>

#ifdef ESP32 // determines compilation for esp32 or arduino comment for arduino nano
const int potiMaxValue = 4096;
const int potiLeftPlayer = 0;
const int potiRightPlayer = 1;
const int multiButton = 5;
#else
const int potMaxValue = 1024;
const int potiLeftPlayer = A0;
const int potiRightPlayer = A1;
const int multiButton = 4;
#endif


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
const int LOWER_BORDER = (SCREEN_HEIGHT - 1);   // Using Screenheight and width -1, 
const int LEFT_BORDER = 0;                      // to make it portable to other displays
const int RIGHT_BORDER = (SCREEN_WIDTH - 1);



// defining game Variables
const int startImageFlipTime = 2000; // intervall to flip between images in start screen
const int timeToGetReady = 2000; // time players have when game starts and after points were made

//the following variables improve ball visibility while waiting for the game to start 
int timeSpentPlayingMillis = 0;
const int middleLineRenderOffset = 400; // determines how long the ball rolls before printing the middle line
bool printMiddleLine = 0;

const int winnerScreenTime = 4000;

int paddleBorderDistance = 10;
int paddleLength = 9;

// states for the startscreen and all the in-game related states.
enum machineState {
  START_SCREEN,
  GET_READY_TO_PLAY,
  IN_GAME,
  LEFT_WINS,
  RIGHT_WINS,
};

machineState currentState = START_SCREEN; // initializing state machine

static unsigned long getReadyTimerMillis = 0;

// header Files
#include "playerManagement.h"
#include "ballManagement.h"
#include "start.h"
#include "pointsManagement.h"
#include "rendering.h"
/****************************************/
// Main Program
/****************************************/

void setup() {
  Serial.begin(9600); 
  Serial.println("Firmware Version 1.0\n");

  pinMode(multiButton, INPUT_PULLUP);
  
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
      static unsigned long bitmapSwitchMillis = 0;  // time cache for image flipping
      static bool picSelector = 0;                  // determines the pic shown (in start.h)
      if (millis() - bitmapSwitchMillis > startImageFlipTime) {
        picSelector = !picSelector;                 //switches the bitmap pics
        bitmapSwitchMillis = millis();
      }
      printStartScreen(picSelector); // prints a bitmap (see start.h)
      
      if(!digitalRead(multiButton)) {   
        getReadyTimerMillis = millis();
        ballInCenter();
        currentState = GET_READY_TO_PLAY;
      }
      break;

    case GET_READY_TO_PLAY:
      printMiddleLine = 0;
      updatePlayers();  // calculates player positions (see playerManagement.h)
      renderScreen();   // renders everything to screen (see rendering.h)
      if(millis() - getReadyTimerMillis > timeToGetReady) {
        timeSpentPlayingMillis = millis();
        currentState = IN_GAME;
      }
      break;

    case IN_GAME:
      
      if (millis() - timeSpentPlayingMillis > middleLineRenderOffset) {
        printMiddleLine = 1;
      }
      updatePlayers(); // playerPosition (playerManagement.h)
      borderCheck(); // checks if the ball hits something, flips direction (see ballManagement.h
      ballPosition(); // calculates ball position (ballManagement.h)
      renderScreen(); // renders frames (rendering.h)
      checkPoints(); // detects if a player made a point (pointsManagement.h)
      break;

    case LEFT_WINS:
      display.clearDisplay(); // prints a bitmap announcing the winner (pointsManagement.h)
      display.drawBitmap(0, 0, leftWins, 128, 32, WHITE);
      display.display();
      delay(winnerScreenTime);
      currentState = START_SCREEN; // return to startscreen
      break;

    case RIGHT_WINS:
      display.clearDisplay(); // prints bitmap announcing winnser 
      display.drawBitmap(0, 0, rightWins, 128, 32, WHITE);
      display.display();
      delay(winnerScreenTime);
      currentState = START_SCREEN;
      break;
      currentState = START_SCREEN; // return to startScreen
  }
}


