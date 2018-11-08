#include <Encoder.h>

// Might cause problems if other libs or code uses attachInterrupt()
#define ENCODER_OPTIMIZE_INTERRUPTS

// We need to use PWM pins to power an RGB LED
// We need to put resistors between the Arduino pin and RGB pin to avoid burning the LED
// Resistors can be from 270 Ohm up to 1 kOhm (the highest value, the lowest the LED will be

// Leonardo
//const int redPin = 10;
//const int greenPin = 11;
//const int bluePin = 12;

// Pro Micro
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 9;

// Common CATHODE RGB LED needs its CATHODE pin to be connected to GND
// Common ANODE RGB LED needs its ANODE pin to be connected to VCC (+5V)
#define COMMON_ANODE // Comment that out if using a common CATHODE LED

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// If the control is reversed, inverse the 2 pins here or directly on your board
// Interupt pins for Leonardo/Pro Micro
Encoder encoder(0, 1);

const int debounceDelay = 40;

const int numberOfLayers = 3;

long encoderCurrentValue;
long encoderLastChange = 0;
// The step allows us to change the "sensibility" of the encoder, we "detect" a change only if the encoder has changed n steps
//  The more steps, the least sensible
const int step = 2;

long encoderNewValue;

// Button pin, digital pin
const int layerUpButtonPin = 10;

int layerUpButtonState = 0;
unsigned long layerUpButtonPreviousTime = 0;
int currentLayer = 0;
int * currentColor = &redValue;

long currentTime;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(layerUpButtonPin, INPUT_PULLUP);

  setColor(redValue, greenValue, blueValue);
}

void loop() {
  currentTime = millis();

  refreshLayer();
  refreshLed();
}

void refreshLayer() {
  int layerUpButtonStateCurrent = digitalRead(layerUpButtonPin);
  
  if (layerUpButtonState != layerUpButtonStateCurrent) {
    // State of the button has changed
    layerUpButtonState = layerUpButtonStateCurrent;

    // To avoid bouncing, we check the last time the button state has been pushed (LOW state)
    //  compare it to our defined interval to validate the push or not
    if (layerUpButtonStateCurrent == LOW
    && currentTime - layerUpButtonPreviousTime >= debounceDelay) {
      layerUpButtonPreviousTime = currentTime;
      currentLayer = (currentLayer + 1) % numberOfLayers;
      if (currentLayer == 0) {
        currentColor = &redValue;
        Serial.println("Switched to red");
      } else if (currentLayer == 1) {
        currentColor = &greenValue;
        Serial.println("Switched to green");
      } else {
        currentColor = &blueValue;
        Serial.println("Switched to blue");
      }
    }
  }
}

void refreshLed() {
  encoderNewValue = encoder.read();
  if ( abs((encoderCurrentValue - encoderNewValue)) >= step ) {
    // Debouncing: consider a change of state is valid if it happens after x milliseconds
    //  If not, we consider it as noise and do nothing
    if (currentTime - encoderLastChange > debounceDelay) {
      if (encoderCurrentValue < encoderNewValue) {
        if (*currentColor > 0) {
          *currentColor = *currentColor - 1;
        }
      } else {
        if (*currentColor < 255) {
          *currentColor = *currentColor + 1;
        }
      }
      setColor(redValue, greenValue, blueValue);
      encoderCurrentValue = encoderNewValue;
      encoderLastChange = currentTime;
    }
  }
}

void setColor(int redVal, int greenVal, int blueVal) {
  #ifdef COMMON_ANODE
    redVal = 255 - redVal;
    greenVal = 255 - greenVal;
    blueVal = 255 - blueVal;
  #endif
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);
  Serial.print("Update RGB LED: ");
  Serial.print(redVal);
  Serial.print(greenVal);
  Serial.println(blueVal);
}
