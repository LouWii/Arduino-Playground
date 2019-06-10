#include <Arduino.h>
#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

SX1509 io; // Create an SX1509 object

const int SX1509_BTN_PIN = 0;

void setup(){
  Serial.begin(9600);

  // Try to connect to the i/o expander
  if (!io.begin(0x3E)) {
    Serial.println("SX1509 not connected");
  } else {
    Serial.println("SX1509 connected");
  }

  // Configure pin 0 as input
  io.pinMode(SX1509_BTN_PIN, INPUT_PULLUP);
}


void loop(){

  // Use io.digitalRead() to check if an SX1509 input I/O is either LOW or HIGH.
  if (io.digitalRead(SX1509_BTN_PIN) == LOW) {
    Serial.println("I/O Expander button pushed");
    while (io.digitalRead(SX1509_BTN_PIN) == LOW)
      ; // Wait for button to release (this is blocking the program)
  }

}
