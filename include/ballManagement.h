//Ball Variables
bool xDirection = 0; // Display x Axis: 0 = left, 1 = rigt
bool yDirection = 0; // Display y Axis: 0 = down, 1 = up

int yPosition = LOWER_BORDER/2; //initializing ball position in the middle of playing field
int xPosition = RIGHT_BORDER/2;

int ySpeed; // defines Speed for y and x axis
int xSpeed; //The Bottleneck for Gamespeed is the i2s bus for the display which has a huge buffer size, game runs just comparably fast on any hardware. therefore the only way to really change the speed is to move the ball 2 pixels at a time

void ballInCenter() { // initial ball position
  yPosition = random(LOWER_BORDER); // randoamizing the initial ball position to make the game more engaging
  xDirection = random(2); 
  yDirection = random(2);
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
  if  ((xPosition == paddleBorderDistance+1 || xPosition == paddleBorderDistance) && 
      (yPosition >= yPositionLeftPlayer && 
      yPosition <= yPositionLeftPlayer + paddleLength)) 
  {
      xDirection = !xDirection;
  }
  if  ((xPosition == RIGHT_BORDER-paddleBorderDistance-1 || xPosition == RIGHT_BORDER-paddleBorderDistance) && 
      (yPosition >= yPositionRightPlayer && 
      yPosition <= yPositionRightPlayer + paddleLength)) 
  {
      xDirection = !xDirection;
  }
}

void ballPosition(){
  static int speedSwitch = 0;     //counts the positionchanges of the ball
  if(speedSwitch<ballSpeed)
    {speedSwitch++;
    xSpeed = 2;
    ySpeed = 2;}
  else{
    speedSwitch = 0;
    xSpeed = 1;
    ySpeed = 1;
}

  if(yDirection) {
    yPosition = yPosition + ySpeed;
  } else {
    yPosition = yPosition - ySpeed;
  }
  if(xDirection) {
    xPosition = xPosition - xSpeed;
  } else {
    xPosition = xPosition + xSpeed;
  }
  
}


