#include <SSD1306Ascii.h>
#include <SSD1306AsciiAvrI2c.h>

#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

char textDisplayed = 3;
const int displayDelay = 3000;
long lastDisplay = 0;

void setup() {
  oled.begin(&Adafruit128x64, I2C_ADDRESS);

  oled.setFont(System5x7);
}

void loop() {
  if (millis() - lastDisplay >= displayDelay || lastDisplay == 0) {

    if (textDisplayed == 3) {
      oled.clear();
      // Characters available in the library are limited
      oled.println("Hello LouWii!");
      oled.println("It's me, Pro Micro!");
      oled.println("=]");

      textDisplayed = 1;
      lastDisplay = millis();
    } else if (textDisplayed == 1) {
      oled.clear();
      // There's no horizontal scrolling effect in this lib
      // However, the lib has an automatic scrolling option, like a terminal, where a new line pushes the old line out
      oled.println("Scrolling? ");

      textDisplayed = 2;
      lastDisplay = millis();
    } else if (textDisplayed == 2) {
      oled.clear();
      // Backslash is "protecting" the next character, we need 2 backslach to display 1
      // The library doesn't display backslashes, displays a white rectangle instead
      oled.println("");
      oled.println("");
      oled.println("   \\\\\\||||||////");
      oled.println("    \\\\  ~ ~  //");
      oled.println("     (  @ @  )");
      oled.println("___oOOo-(_)-oOOo___");

      textDisplayed = 3;
      lastDisplay = millis();
    }

  }
}
