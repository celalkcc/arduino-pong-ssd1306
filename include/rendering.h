void renderScreen() {
  display.clearDisplay();
  display.drawLine(
    paddleBorderDistance,
    yPositionLeftPlayer,
    paddleBorderDistance,
    yPositionLeftPlayer + paddleLength,
    WHITE
  );
  display.drawLine(
    RIGHT_BORDER - paddleBorderDistance, // calculating the paddles distance to the border
    yPositionRightPlayer, // +/- paddleRadius takes care of edge clipping
    RIGHT_BORDER - paddleBorderDistance,
    yPositionRightPlayer + paddleLength,
    WHITE
  );
  //drawBall
  display.drawPixel(xPosition, yPosition, WHITE);
  display.println();
  display.display();
}

