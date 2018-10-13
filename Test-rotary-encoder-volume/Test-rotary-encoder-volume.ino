// Requires Project-HID lib https://github.com/NicoHood/HID
// Requires encoder lib https://www.pjrc.com/teensy/td_libs_Encoder.html

#include <Encoder.h>
#include <HID-Project.h>
#include <HID-Settings.h>

// Might cause problems if other libs or code uses attachInterrupt()
#define ENCODER_OPTIMIZE_INTERRUPTS

Encoder encoder(0, 1);

long encod = 0;
const int step = 2;

void setup() {
  Serial.begin(9600);

  Consumer.begin();
}

void loop() {
  long newEnc;

  newEnc = encoder.read();
  if ( abs((encod - newEnc)) == step ) {

    // Control sound?
    if (encod < newEnc) {
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    encod = newEnc;
    Serial.println(newEnc);
    delay(20);
  }
}
