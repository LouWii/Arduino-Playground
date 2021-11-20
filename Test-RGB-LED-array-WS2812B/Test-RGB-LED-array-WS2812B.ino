// https://github.com/FastLED/FastLED - http://fastled.io/ FastLED lib
#include <FastLED.h>

#define LED_PIN     7

// Our LED array is 8*8 = 64 LEDs
#define NUM_LEDS   64

CRGB leds[NUM_LEDS];

int ledIdx = 0;
int previousLed = NUM_LEDS - 1;

// Change LED every n ms
int ledChangeDelay = 100;

long prevActionTime = 0;
long currentTime;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
}

void loop() {
    // Avoiding using delay() by checking time on each iteration 
    currentTime = millis();

    if (currentTime - prevActionTime > ledChangeDelay) {
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
        prevActionTime = currentTime;
    }
}
