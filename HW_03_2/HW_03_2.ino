const int BledPin = 3;
const int pushButton = 10;

int clickCount = 0;


unsigned long previousMillis = 0;
unsigned long lastPressTime = 0;
int ledState = HIGH;

void setup() {
  pinMode(BledPin, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (digitalRead(pushButton) == LOW) {
    if (currentMillis - lastPressTime > 200) {
      clickCount++;
      if (clickCount > 3) {
        clickCount = 0;
      }
      lastPressTime = currentMillis;
      
    
      ledState = LOW; 
      digitalWrite(BledPin, ledState);
      previousMillis = currentMillis;
    }
  }

 
  if (clickCount == 0) {
  
    digitalWrite(BledPin, LOW);
  } 
  else {
  
    int interval = 0;

    if (clickCount == 1) {
      interval = 500;
    } 
    else if (clickCount == 2) {
      interval = 150;
    } 
    else if (clickCount == 3) {
      interval = 50;
    }

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

    
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      
      digitalWrite(BledPin, ledState);
    }
  }
}