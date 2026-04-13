//Ball Variables
bool xDirection = 0; // Display x Axis: 0 = left, 1 = rigt
bool yDirection = 0; // Display y Axis: 0 = down, 1 = up

int yPosition = LOWER_BORDER/2; //initializing ball position in the middle of playing field
int xPosition = RIGHT_BORDER/2;

void ballInCenter() { // initial ball position
  yPosition = random(LOWER_BORDER);
  xPosition = RIGHT_BORDER/2;
}

void borderCheck(){
  // direction switches for walls:
  if(yPosition >= LOWER_BORDER) {
    yDirection = !yDirection;
  } 
  if (yPosition <= UPPER_BORDER) {
    yDirection = !yDirection;
  }
  //direction switches for paddles:
  if  (xPosition == paddleBorderDistance+1 && 
      (yPosition >= yPositionLeftPlayer && 
      yPosition <= yPositionLeftPlayer + paddleLength)) 
  {
      xDirection = !xDirection;
  }
  if  (xPosition == RIGHT_BORDER-paddleBorderDistance-1 && 
      (yPosition >= yPositionRightPlayer && 
      yPosition <= yPositionRightPlayer + paddleLength)) 
  {
      xDirection = !xDirection;
  }
}

void ballPosition(){
  if(yDirection) {
    yPosition--;
  } else {
    yPosition++;
  }
  if(xDirection) {
    xPosition++;
  } else {
    xPosition--;
  }
}


