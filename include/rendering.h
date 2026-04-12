void renderScreen() {
  display.clearDisplay();
  display.drawLine(
    borderDistance,
    yPositionLeftPlayer,
    borderDistance,
    yPositionLeftPlayer + paddleLength,
    WHITE
  );
  display.drawLine(
    RIGHT_BORDER - borderDistance, // calculating the paddles distance to the border
    yPositionRightPlayer, // +/- paddleRadius takes care of edge clipping
    RIGHT_BORDER - borderDistance,
    yPositionRightPlayer + paddleLength,
    WHITE
  );
  //drawBall
  display.drawPixel(xPosition, yPosition, WHITE);
  display.println();
  display.display();
}

