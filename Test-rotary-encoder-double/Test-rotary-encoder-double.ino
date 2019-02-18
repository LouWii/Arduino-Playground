// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html

#include <Encoder.h>

// Might cause problems if other libs or code uses attachInterrupt()
// #define ENCODER_OPTIMIZE_INTERRUPTS

// If the control is reversed, inverse the 2 pins here or directly on your board
Encoder encoder1(10, 16);
Encoder encoder2(0, 1);

const int debounceDelay = 40;

long encoder1CurrentValue;
long encoder1LastChange = 0;
long encoder2CurrentValue;
long encoder2LastChange = 0;
// The step allows us to change the "sensibility" of the encoder, we "detect" a change only if the encoder has changed n steps
//  The more steps, the least sensible
const int step = 1;

long currentTime;
long encoder1NewValue;
long encoder2NewValue;

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();

  encoder1NewValue = encoder1.read();
  if ( abs((encoder1CurrentValue - encoder1NewValue)) >= step ) {
    // Debouncing: consider a change of state is valid if it happens after x milliseconds
    //  If not, we consider it as noise and do nothing
    if (currentTime - encoder1LastChange > debounceDelay) {
      if (encoder1CurrentValue < encoder1NewValue) {
        // Going up
        printEncoderInfo("Encoder1", "Up", encoder1LastChange, encoder1NewValue, encoder1CurrentValue);
      } else {
        // Going down
        printEncoderInfo("Encoder1", "Down", encoder1LastChange, encoder1NewValue, encoder1CurrentValue);
      }
      encoder1CurrentValue = encoder1NewValue;
      encoder1LastChange = currentTime;
    }
  }

  encoder2NewValue = encoder2.read();
  if ( abs((encoder2CurrentValue - encoder2NewValue)) >= step ) {
    // Debouncing: consider a change of state is valid if it happens after x milliseconds
    //  If not, we consider it as noise and do nothing
    if (currentTime - encoder2LastChange > debounceDelay) {
      if (encoder2CurrentValue < encoder2NewValue) {
        // Going up
        printEncoderInfo("Encoder2", "Up", encoder2LastChange, encoder2NewValue, encoder2CurrentValue);
      } else {
        // Going down
        printEncoderInfo("Encoder2", "Down", encoder2LastChange, encoder2NewValue, encoder2CurrentValue);
      }
      encoder2CurrentValue = encoder2NewValue;
      encoder2LastChange = currentTime;
    }
  }
}

static void printEncoderInfo(char encoderName[], char encoderDirection[], long encoderLastChange, long encoderNewValue, long encoderCurrentValue) {
  Serial.print(encoderName);
  Serial.print(": ");
  Serial.print(encoderDirection);
  Serial.println("!");
  Serial.print("Time: ");
  Serial.print(currentTime);
  Serial.print("; Last time: ");
  Serial.print(encoderLastChange);
  Serial.print("; Encoder value: ");
  Serial.print(encoderNewValue);
  Serial.print("; Encoder last value: ");
  Serial.println(encoderCurrentValue);
}
