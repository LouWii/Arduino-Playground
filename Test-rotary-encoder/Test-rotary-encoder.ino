// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html

#include <Encoder.h>

// Might cause problems if other libs or code uses attachInterrupt()
#define ENCODER_OPTIMIZE_INTERRUPTS

// If the control is reversed, inverse the 2 pins here or directly on your board
Encoder encoder(0, 1);

const int debounceDelay = 20;

long encoderCurrentValue;
long encoderLastChange = 0;
// The step allows us to change the "sensibility" of the encoder, we "detect" a change only if the encoder has changed n steps
//  The more steps, the least sensible
const int step = 1;

long currentTime;
long encoderNewValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();

  encoderNewValue = encoder.read();
  if ( abs((encoderCurrentValue - encoderNewValue)) >= step ) {
    // Debouncing: consider a change of state is valid if it happens after x milliseconds
    //  If not, we consider it as noise and do nothing
    if (currentTime - encoderLastChange > debounceDelay) {
      if (encoderCurrentValue < encoderNewValue) {
        // Going up
      } else {
        // Going down
      }
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
