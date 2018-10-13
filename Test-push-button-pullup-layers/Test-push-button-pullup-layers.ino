
const long buttonPressInterval = 50;

// Layers
const int layerUpButtonPin = 2;
int layerUpButtonState = 0;
unsigned long layerUpButtonPreviousTime = 0;
int currentLayer = 0;


// Built-in
const int LEDPIN = LED_BUILTIN;

void setup() {
  Serial.begin(9600);

  // Inputs
  pinMode(layerUpButtonPin, INPUT_PULLUP);

  // Led ouput
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // To avoid bouncing, we check the last time the button state has been pushed (LOW state)
  //  compare it to our defined interval to validate the push or not
  int layerBtnVal = digitalRead(layerUpButtonPin);
  if (currentMillis - layerUpButtonPreviousTime >= buttonPressInterval && layerUpButtonState != layerBtnVal) {
    layerUpButtonPreviousTime = currentMillis;

    if (layerBtnVal == HIGH) {

    } else {
      
      currentLayer += 1;

      // add a short delay to loop so that the computer's serial buffer is not filled as fast
      Serial.println(currentLayer);
      delay(2);
    }
  }
  layerUpButtonState = layerBtnVal;

  if (currentLayer % 4 == 0) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
}

void layerSelect() {

}
