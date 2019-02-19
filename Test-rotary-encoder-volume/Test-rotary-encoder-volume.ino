 // Requires Project-HID lib https://github.com/NicoHood/HID
// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html

#include <Encoder.h>
#include <HID-Project.h>
#include <HID-Settings.h>

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

  Consumer.begin();
}

void loop() {
  currentTime = millis();

  encoderNewValue = encoder.read();
  if ( abs((encoderCurrentValue - encoderNewValue)) >= step ) {

    if (currentTime - encoderLastChange > debounceDelay) {
      if (encoderCurrentValue < encoderNewValue) {
        Consumer.write(MEDIA_VOLUME_UP);
        Serial.println("Volume Up");
      } else {
        Consumer.write(MEDIA_VOLUME_DOWN);
        Serial.println("Volume Down");
      }
      encoderCurrentValue = encoderNewValue;
      encoderLastChange = currentTime;
    }
  }
}
