int borderDistance = 5;
int paddleLength = 18;
int yPositionLeftPlayer = 0;
int yPositionRightPlayer = 0;


void updatePlayers() {
  int potiValueL = analogRead(potiLeftPlayer);
  yPositionLeftPlayer = map(
                                  potiValueL, 
                                  0, 
                                  1023, 
                                  UPPER_BORDER, 
                                  LOWER_BORDER - paddleLength); // substracting Paddlelength takes care of paddles edge clipping
  // mapping the poti values to the Y-Axis Borders of the Screen.

  int potiValueR = analogRead(potiRightPlayer);
  yPositionRightPlayer = map(
                                  potiValueR, 
                                  0, 
                                  1023, 
                                  UPPER_BORDER, // +/- paddleRadius takes care of edge clipping
                                  LOWER_BORDER - paddleLength); 
  // mapping the poti values to the Y-Axis Borders of the Screen.
}












































/****************************************/
// Left Player
/****************************************

int borderDistance = 5;
int paddleRadius = 6;
int yPositionLeftPlayer = 0;
int yPositionRightPlayer = 0;



void updatePlayers() {
  int potiValueL = analogRead(potiLeftPlayer);
  yPositionLeftPlayer = map(
                            potiValueL, 
                            0, 
                            1023, 
                            UPPER_BORDER + paddleRadius, // +/- paddleRadius takes care of edge clipping
                            LOWER_BORDER - paddleRadius); 
  // mapping the poti values to the Y-Axis Borders of the Screen.

  int potiValueR = analogRead(potiRightPlayer);
  yPositionRightPlayer = map(
                                  potiValueR, 
                                  0, 
                                  1023, 
                                  UPPER_BORDER + paddleRadius, // +/- paddleRadius takes care of edge clipping
                                  LOWER_BORDER - paddleRadius); 
  // mapping the poti values to the Y-Axis Borders of the Screen.
  display.drawLine(
    borderDistance,
    yPositionLeftPlayer + paddleRadius,
    borderDistance,
    yPositionLeftPlayer - paddleRadius,
    WHITE
  );
  display.drawLine(
    RIGHT_BORDER - borderDistance, // calculating the paddles distance to the border
    yPositionRightPlayer + paddleRadius, // +/- paddleRadius takes care of edge clipping
    RIGHT_BORDER - borderDistance,
    yPositionRightPlayer - paddleRadius,
    WHITE
  );
  display.display();
}
*/