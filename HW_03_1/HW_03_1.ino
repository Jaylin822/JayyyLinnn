const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int buttonState = 0;
bool buttonPressed = false;
unsigned long pressingTime = 0;
int longPressInterval = 2000;


int lightNum = 0;
int RLightColor = 0;
int GLightColor = 0;
int BLightColor = 0;


int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;


int RCurrentColor = 0;
int GCurrentColor = 0;
int BCurrentColor = 0;


const int fadeAmount = 2;
int fadeDirection = 1;



void setup() {

  // initialize digital pin LED_BUILTIN as an output.

  pinMode(buttonPin, INPUT);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

}



// the loop function runs over and over again forever

void loop(){

  checkButton();
  updateLEDColor();
  setRGBLEDColor(RCurrentColor, GCurrentColor, BCurrentColor);

}

void changeMode(){
    currentMode++;
  if(currentMode >= 3){
    currentMode = 0;
  }

  if(currentMode == 1){
    blinkTimer = 0;
    blinkOn = true;
  }

  if(currentMode == 2){
    fadeDirection = 1;
  }
}



void checkButton() {

  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && !buttonPressed){
    pressingTime = millis();
    buttonPressed = true;
  }

  if(buttonState == LOW && buttonPressed){
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      changeLEDColor();
    }

    else{
      changeMode();
    }

    buttonPressed = false;
  }
}



void setRGBLEDColor(int r, int g, int b){

  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
}



void changeLEDColor(){
  lightNum++;

  if(lightNum >= 5){
    lightNum = 0;
  }



  if(lightNum == 0){

    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 0;
  }



  if(lightNum == 1){

    RLightColor = 0;
    GLightColor = 255;
    BLightColor = 255;
  }



  if(lightNum == 2){

    RLightColor = 255;
    GLightColor = 0;
    BLightColor = 255;
  }



  if(lightNum == 3){

    RLightColor = 255;
    GLightColor = 255;
    BLightColor = 0;
  }



  if(lightNum == 4){

    RLightColor = 0;
    GLightColor = 0;
    BLightColor = 255;
  }

  RCurrentColor = RLightColor;
  GCurrentColor = GLightColor;
  BCurrentColor = BLightColor;
}





void updateLEDColor(){

  if(currentMode == 0){
    RCurrentColor = RLightColor;
    GCurrentColor = GLightColor;
    BCurrentColor = BLightColor;
  }



  else if(currentMode == 1){

    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }



    if(blinkOn){
      RCurrentColor = RLightColor;
      GCurrentColor = GLightColor;
      BCurrentColor = BLightColor;
    }

    else{
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }

  }

  else if( currentMode == 2){
    bool negativeDir = false;

    if(RLightColor == 0){
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if(RCurrentColor > (255 - RLightColor) || (RCurrentColor < 0)){
        negativeDir = true;
      }
      if(RCurrentColor < 0) RCurrentColor = 0;
      if(RCurrentColor > 255) RCurrentColor = 255;
    }

    if(GLightColor == 0){
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if(GCurrentColor > (255 - GLightColor) || (GCurrentColor < 0)){
        negativeDir = true;
      }
      if(GCurrentColor < 0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
    }

    if(BLightColor == 0){
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if(BCurrentColor > (255 - BLightColor) || (BCurrentColor < 0)){
        negativeDir = true;
      }
      if(BCurrentColor < 0) BCurrentColor = 0;
      if(BCurrentColor > 255) BCurrentColor = 255;
    }

    if(negativeDir)
      fadeDirection = -fadeDirection;

    delay(10); 
  }
}


 