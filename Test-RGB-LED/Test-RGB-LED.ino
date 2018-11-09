// We need to use PWM pins to power an RGB LED
// We need to put resistors between the Arduino pin and RGB pin to avoid burning the LED
// Resistors can be from 270 Ohm up to 1 kOhm (the highest value, the lowest the LED will be

// Leonardo
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

// Pro Micro
//const int redPin = 5;
//const int greenPin = 6;
//const int bluePin = 9;

// Common CATHODE RGB LED needs its CATHODE pin to be connected to GND
// Common ANODE RGB LED needs its ANODE pin to be connected to VCC (+5V)
#define COMMON_ANODE // Comment that out if using a common CATHODE LED

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
    setColor(20, 0, 0);
    delay(1000);
    setColor(0, 20, 0);
    delay(1000);
    setColor(0, 0, 20);
    delay(1000);
    setColor(0, 20, 20);
    delay(1000);
    setColor(20, 0, 20);
    delay(1000);
    setColor(20, 20, 0);
    delay(1000);
}

void setColor(int redValue, int greenValue, int blueValue) {
  #ifdef COMMON_ANODE
    redValue = 255 - redValue;
    greenValue = 255 - greenValue;
    blueValue = 255 - blueValue;
  #endif
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
