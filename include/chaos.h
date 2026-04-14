unsigned long chaosClock = 0;
bool chaosFlag = 0;

void chaosInit() {
    if(!digitalRead(multiButton)) {
        chaosFlag = 1;
        chaosClock = millis();
    }
}

void chaosMode() {
    if (millis() - chaosClock >= chaosModeTime) {
        chaosFlag = 0;
    }
    if (chaosFlag) {
        paddleLength = random(LOWER_BORDER);  
        paddleBorderDistance = random(RIGHT_BORDER/2);
    }
}
