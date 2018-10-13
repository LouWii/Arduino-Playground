// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html

#include <Encoder.h>

// Might cause problems if other libs or code uses attachInterrupt()
#define ENCODER_OPTIMIZE_INTERRUPTS

Encoder encoder(1, 0);

long encod;
const int step = 2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  long newEnc;

  newEnc = encoder.read();
  if ( abs((encod - newEnc)) == step ) {

    // Control sound?
    if (encod < newEnc) {
      Keyboard.begin();
      Keyboard.print("VolUp");
      Keyboard.end();
    } else {
      Keyboard.begin();
      Keyboard.print("VolDn");
      Keyboard.end();
    }
    encod = newEnc;
    Serial.println(newEnc);
    delay(20);
  }
}
