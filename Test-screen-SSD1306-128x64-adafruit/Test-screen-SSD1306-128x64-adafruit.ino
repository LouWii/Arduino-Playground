#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The address is very often 0x3C or 0x3D,
//  try one or the other if you don't know which one your screen is using
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);

char textDisplayed = 3;
const int displayDelay = 3000;
long lastDisplay = 0;

// This verifies that the library has been changed properly for the screen size
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
}

void loop() {
  // My screen is one color only but this is needed anyway
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);

  if (millis() - lastDisplay >= displayDelay || lastDisplay == 0) {

    if (textDisplayed == 3) {
      oled.clearDisplay();
      // Characters available in the library are limited
      oled.setTextSize(1);
      oled.println("Hello LouWii!");
      oled.println("It's me, Pro Micro!");
      oled.println("=]");
      oled.display();

      textDisplayed = 1;
      lastDisplay = millis();
    } else if (textDisplayed == 1) {
      oled.clearDisplay();
      oled.setTextSize(2);
      oled.println("Scrolling? ");
      // Interestingly, calling .display() after the startscrollleft is making the scrolling effect all buggy
      oled.display();
      oled.startscrollleft(0x00, 0x0F);

      textDisplayed = 2;
      lastDisplay = millis();
    } else if (textDisplayed == 2) {
      oled.stopscroll();
      oled.clearDisplay();
      oled.setTextSize(1);
      // Backslash is "protecting" the next character, we need 2 backslach to display 1
      oled.println("");
      oled.println("");
      oled.println("   \\\\\\||||||////");
      oled.println("    \\\\  ~ ~  //");
      oled.println("     (  @ @  )");
      oled.println("___oOOo-(_)-oOOo___");
      oled.display();

      textDisplayed = 3;
      lastDisplay = millis();
    }

  }
}
