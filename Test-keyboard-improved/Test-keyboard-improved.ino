// Requires Project-HID lib https://github.com/NicoHood/HID

#include <HID-Project.h>
#include <HID-Settings.h>


const long buttonPressInterval = 50;

const int buttonPin = 3;

int buttonState = 0;
unsigned long buttonPreviousTime = 0;

void setup() {
  Serial.begin(9600);

  // Inputs
  pinMode(buttonPin, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  // Keyboard is for "standard" US layout keyboard keys
  //Keyboard.begin();
  // Consumer is for "media" keys liek player control, volume control, apps (internet browser...)
  Consumer.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // To avoid bouncing, we check the last time the button state has been pushed (LOW state)
  //  compare it to our defined interval to validate the push or not
  int buttonValue = digitalRead(buttonPin);
  if (currentMillis - buttonPreviousTime >= buttonPressInterval && buttonState != buttonValue) {
    buttonPreviousTime = currentMillis;

    if (buttonValue == HIGH) {

    } else {
      // add a short delay to loop so that the computer's serial buffer is not filled as fast
      Serial.println("Pushed");

      // Codes for keyboard keys are in https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf page 53
      // or here in a more rough version http://www.freebsddiary.org/APC/usb_hid_usages
      

      // Doesn't work on Windows, only on Linux because only Linux respects the HID USB standards
      // HELL YEAH TO STANDARDS, BOOH at Windows
      //Keyboard.write(KEY_VOLUME_UP);
      //Keyboard.write(HID_KEYBOARD_VOLUME_UP);

      // o key
      //Keyboard.write(HID_KEYBOARD_O_AND_O);
      
      // Use the default print functions
      //Keyboard.println("Hello World!");

      // Press a single character, special non ascii characters wont work.
      //Keyboard.write('a');

      // Write single keys, do not use a number here!
      //Keyboard.write(KEY_ENTER);

      // If you really wish to press a RAW keycode without the name use this:
      // equivalent of KEY_ENTER
      //Keyboard.write(KeyboardKeycode(40));

      // key code for letter m
      //Keyboard.write(KeyboardKeycode(0x10));

      // letter i 0x0C = 12
      //Keyboard.write(KeyboardKeycode(0x0C));

      // F1 key
      //Keyboard.write(KeyboardKeycode(0x3A));

      // Use (a limited number of) consumer keys.
      // Only works with the lower 255 keys and on linux only.
      //Keyboard.write(MEDIA_PLAY_PAUSE);

      // Linux also supports several system function via consumer report.
      //Keyboard.write(CONSUMER_POWER);
      //Keyboard.write(CONSUMER_SLEEP);

      // You can also use some special keyboard keys on linux.
      //Keyboard.write(KEY_POWER);
      //Keyboard.write(KEY_F13);

      // You can wakeup you PC from sleep.
      // This might be not supported on all hardware, but on all OS types.
      //Keyboard.wakeupHost();

      // WINDOWS, not all is lost, we have the Consumer API in HID-project! Yay \o/
      // Consumer codes are there https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf page 75 
      //  but it's quite a mess, there are a lot because it's all for softwares and whatnot
      // The most important ones are defined in the HID lib
      // Media: MEDIA_FAST_FORWARD 0xB3 MEDIA_REWIND 0xB4 MEDIA_NEXT 0xB5 MEDIA_PREVIOUS 0xB6 MEDIA_STOP 0xB7 MEDIA_PLAY_PAUSE 0xCD
      // Volume: MEDIA_VOLUME_MUTE 0xE2 MEDIA_VOLUME_UP 0xE9 MEDIA_VOLUME_DOWN 0xEA
      
      Consumer.write(MEDIA_VOLUME_UP);
    }
  }
  buttonState = buttonValue;
}
