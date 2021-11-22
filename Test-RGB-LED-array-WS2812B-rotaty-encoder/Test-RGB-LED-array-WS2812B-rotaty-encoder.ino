// https://github.com/FastLED/FastLED - http://fastled.io/ FastLED lib
#include <FastLED.h>
// https://www.pjrc.com/teensy/td_libs_Encoder.html - "Encoder" by Paul Stoffregen in Arduino IDE
#include <Encoder.h>

// Mode 0: encoder controls number of lit LEDs; mode 1: encoder controls the speed of LED loop; mode 2: encoder controls the brightness of all the LEDs
#define SCRIPT_MODE 2

/****************** Vars for LED control ******************/
#define LED_PIN     7

// Our LED array is 8*8 = 64 LEDs
#define NUM_LEDS   64

#define SPEED_STEP 7

#define BRIGHTNESS_STEP 5;

CRGB leds[NUM_LEDS];

int ledIdx = 0;
int previousLed = NUM_LEDS - 1;

// Change LED every n ms
int ledChangeDelay = 100;

int litLEDs = 1;

int ledBrightness = 20;

/****************** Vars for rotary encoder ******************/
// If the control is reversed, inverse the 2 pins here or directly on your board
Encoder encoder(0, 1);

const int debounceDelay = 10;
long encoderNewValue;
long encoderCurrentValue;
long encoderLastChange = 0;

// The step allows us to change the "sensibility" of the encoder, we "detect" a change only if the encoder has changed n steps
//  The more steps, the least sensible
const int encoderStep = 4;

long prevActionTime = 0;
long currentTime;

void setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(ledBrightness); // 0 -255 value
  
    if (SCRIPT_MODE == 0) {
        ledChangeDelay = 0;
    } else if (SCRIPT_MODE == 2) {
        ledBrightness = 5;
        // Set all LEDs to a color so they all lit up
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB::Indigo;
        }   
    }
}

void encoderAction(int dir) {
    if (SCRIPT_MODE == 0) {
        if (dir) {
            if (litLEDs < NUM_LEDS) {
                litLEDs++;
            }
        } else if (litLEDs > 0) {
            litLEDs--;
        }
    } else if (SCRIPT_MODE == 1) {
        if (dir) {
            // Going up == going faster
            if (ledChangeDelay > SPEED_STEP) {
                ledChangeDelay -= SPEED_STEP;
            }
        } else {
            // Going down == going slower
            ledChangeDelay += SPEED_STEP;
        }
    } else if (SCRIPT_MODE == 2) {
        if (dir) {
            // Going up == going brighter
            if (ledBrightness < 255) {
                ledBrightness += BRIGHTNESS_STEP;
            }
        } else {
            if (ledBrightness > 0) {
                ledBrightness -= BRIGHTNESS_STEP;
            }
        }
    }
}

void updateLEDs() {
    if (SCRIPT_MODE == 0) {
        // Reset all LEDs
        for (int i = 0; i < NUM_LEDS; i++) {
            leds[i] = CRGB::Black;
        }
        // Light up only the ones we need
        for (int i = 0; i < litLEDs; i++) {
            leds[i] = CRGB::SlateBlue;
        }

        FastLED.show();
    } else if (SCRIPT_MODE == 1) {
        leds[previousLed] = CRGB::Black;
        //leds[ledIdx] = CRGB::Red;
        //leds[ledIdx] = 0x3344DD;
        leds[ledIdx].setRGB(2, 2, 222);
        FastLED.show();
        
        if (ledIdx == NUM_LEDS - 1) {
          ledIdx = 0;
        } else {
          ledIdx++;
        }
        if (ledIdx == 0) {
            previousLed = NUM_LEDS - 1;
        } else {
            previousLed = ledIdx - 1;
        }
    } else if (SCRIPT_MODE == 2) {
        FastLED.setBrightness(ledBrightness);
        FastLED.show();
    }
}

void loop() {
    // Avoiding using delay() by checking time on each iteration 
    currentTime = millis();

    encoderNewValue = encoder.read();
    if (currentTime - encoderLastChange > debounceDelay) {
    
        // Debouncing: consider a change of state is valid if it happens after x milliseconds
        //  If not, we consider it as noise and do nothing
        if ( abs((encoderCurrentValue - encoderNewValue)) >= encoderStep ) {
            if (encoderCurrentValue < encoderNewValue) {
                encoderAction(1);
            } else {
                encoderAction(0);
            }
            encoderCurrentValue = encoderNewValue;
            encoderLastChange = currentTime;
        }
    }

    if (currentTime - prevActionTime > ledChangeDelay) {
        updateLEDs();
        prevActionTime = currentTime;
    }
}
