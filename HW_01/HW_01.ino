const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool isRunning = false;

void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !isRunning) {
    isRunning = true;
    delay(300);
  }


  if (isRunning) {
 
    runColorState(255, 255, 255);
    runColorState(0, 255, 255);
    runColorState(255, 0, 255);
    runColorState(255, 255, 0);
    runColorState(0, 0, 255);
    runColorState(0, 255, 0);
    runColorState(255, 0, 0);
    runColorState(0, 0, 0);

    isRunning = false; 
  }
}

void runColorState(int r, int g, int b) {
  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
  delay(1000);

  int startR = r, startG = g, startB = b;
  for (int step = 0; step <= 50; step++) {
    int currentR = map(step, 0, 50, startR, 255);
    int currentG = map(step, 0, 50, startG, 255);
    int currentB = map(step, 0, 50, startB, 255);

    analogWrite(RledPin, currentR);
    analogWrite(GledPin, currentG);
    analogWrite(BledPin, currentB);
    delay(15);
  }
}