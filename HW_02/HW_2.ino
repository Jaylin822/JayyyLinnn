const int buttonPin = 2;

const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;
const int redBlinkPin = 8;

int mood = 0;
const int neutralMood = 10;
int buttonState = 0;
int fadingDirection = 1;
bool buttonPressed = false;

unsigned long previousMillis = 0; 
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

unsigned long redBlinkPreviousMillis = 0;
bool redLedState = LOW;

const long unTouchInterval = 5000;
const long reducedInterval = 1000; 


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  pinMode(redBlinkPin, OUTPUT);

  mood = neutralMood;
}

void loop() {
  showLEDState(mood);

  updateRedBlink(mood);

  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && !buttonPressed){
    mood++;
    if(mood > 20)  mood=20;

    touchedTimer = millis();
    buttonPressed = true;
  }
  if(buttonState == LOW && buttonPressed){
    buttonPressed = false;
  }

  unsigned long currentTimer = millis();
  if(currentTimer - touchedTimer > unTouchInterval){
    if(currentTimer - reducedTimer > reducedInterval){
      mood--;
      if(mood < 0) mood = 0;
      reducedTimer = currentTimer;
    }
  }
}


void showLEDState(int mood){

  float brightnessInterval = 255 / 10.0;

  if(mood == 20) {
    analogWrite(RledPin, random(0, 256));
    analogWrite(GledPin, random(0, 256));
    analogWrite(BledPin, random(0, 256));
  }
  else if(mood >= neutralMood){
    analogWrite(RledPin, 255);
    analogWrite(GledPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BledPin, 255 - brightnessInterval * (mood - neutralMood));
  }
  else{
    analogWrite(RledPin, 255 - brightnessInterval * (neutralMood - mood));
    analogWrite(GledPin, brightnessInterval * (neutralMood - mood));
    analogWrite(BledPin, 255);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > 1000){
    mood = mood + fadingDirection;
    if(mood >= 20 || mood <= 0)
      fadingDirection = -fadingDirection;
    previousMillis = currentMillis;
  }
}

void updateRedBlink(int mood) {

  long blinkInterval = map(mood, 0, 20, 600, 80);

  unsigned long currentMillis = millis();

  if (currentMillis - redBlinkPreviousMillis >= blinkInterval) {
    redBlinkPreviousMillis = currentMillis;

    if (redLedState == LOW) {
      redLedState = HIGH;
    } else {
      redLedState = LOW;
    }
    digitalWrite(redBlinkPin, redLedState);
  }
}