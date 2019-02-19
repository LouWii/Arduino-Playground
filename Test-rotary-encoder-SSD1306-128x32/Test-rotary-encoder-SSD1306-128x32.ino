// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html
#include <Encoder.h>

// If the control is reversed, inverse the 2 pins here or directly on your board
Encoder encoder(9, 10);

#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>

#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

const int debounceDelay = 40;

long encoderCurrentValue;
long encoderLastChange = 0;
// The step allows us to change the "sensibility" of the encoder, we "detect" a change only if the encoder has changed n steps
//  The more steps, the least sensible
const int step = 2;

long currentTime;
long encoderNewValue;

void setup() {
  Serial.begin(9600);

  oled.begin(&Adafruit128x32, I2C_ADDRESS);

  oled.setFont(System5x7);
}

void loop() {
  currentTime = millis();

  encoderNewValue = encoder.read();
  if ( abs((encoderCurrentValue - encoderNewValue)) >= step ) {
    // Debouncing: consider a change of state is valid if it happens after x milliseconds
    //  If not, we consider it as noise and do nothing
    if (currentTime - encoderLastChange > debounceDelay) {
      oled.clear();
      if (encoderCurrentValue < encoderNewValue) {
        // Going up
        Serial.println("Up!");
        oled.println("Up!");
      } else {
        // Going down
        Serial.println("Down!");
        oled.println("Down!");
      }
      oled.print("Time: ");
      oled.println(currentTime);
      oled.print("Current value: ");
      oled.println(encoderNewValue);
      Serial.print("Time: ");
      Serial.print(currentTime);
      Serial.print("; Last time: ");
      Serial.print(encoderLastChange);
      Serial.print("; Encoder value: ");
      Serial.print(encoderNewValue);
      Serial.print("; Encoder last value: ");
      Serial.println(encoderCurrentValue);
      encoderCurrentValue = encoderNewValue;
      encoderLastChange = currentTime;
    }
  }
}
