void drawCenterLine() {
  int centerX = SCREEN_WIDTH / 2;

  for (int y = 0; y < SCREEN_HEIGHT; y += 6) {
    display.drawLine(centerX, y, centerX, y + 1, WHITE);
  }
}

void drawScore() {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Left player
  display.setCursor(30, 0);
  display.print(lPlayerPoints);

  // Right player
  display.setCursor(90, 0);
  display.print(rPlayerPoints);
}

void renderScreen() {
  display.clearDisplay();
  drawCenterLine();
  drawScore();
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

