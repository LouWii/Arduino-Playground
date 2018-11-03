#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// The address is very often 0x3C or 0x3D,
//  try one or the other if you don't know which one your screen is using
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);

char textDisplayed = 4;
const int displayDelay = 3000;
long lastDisplay = 0;

// 128x64 logo image converted to bytes with http://javl.github.io/image2cpp/
// Background color: black, Code output format Arduino code, single bitmap, Draw mode horizontal
// We use PROGMEM to not overload the SRAM (https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)
const uint8_t logoBitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3e, 0x00, 
  0x00, 0x08, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x04, 0x00, 0x20, 0x02, 0x00, 0x10, 0x3f, 0x7e, 0x00, 
  0x00, 0x3c, 0x00, 0x00, 0x1e, 0xff, 0xf0, 0x0c, 0x00, 0x38, 0x06, 0x00, 0x1c, 0x3f, 0x7e, 0x00, 
  0x00, 0xff, 0x00, 0x00, 0x7f, 0xbf, 0xf8, 0x3c, 0x00, 0x3c, 0x1e, 0x00, 0x1e, 0x3f, 0x7e, 0x00, 
  0x03, 0xff, 0xc0, 0x01, 0xff, 0xef, 0xfe, 0xfc, 0x00, 0x3f, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0xff, 0x40, 0x01, 0x7f, 0x87, 0xfa, 0xbc, 0x00, 0x3f, 0x7e, 0x00, 0x1f, 0xbd, 0x7a, 0x00, 
  0x00, 0x3d, 0xc0, 0x01, 0xde, 0x01, 0xfe, 0xec, 0x00, 0x3f, 0x7e, 0x00, 0x1f, 0xb7, 0x6e, 0x00, 
  0x00, 0x0f, 0xc0, 0x01, 0xf4, 0x00, 0x5e, 0xfc, 0x00, 0x3f, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0x81, 0xf8, 0x00, 0x7e, 0xfc, 0x00, 0x2f, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0xe1, 0xf8, 0x00, 0x7e, 0xfc, 0x00, 0xff, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0xf1, 0xf8, 0x00, 0x7e, 0xfc, 0x03, 0xfd, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0xfd, 0xf8, 0x00, 0x7e, 0xfc, 0x07, 0xff, 0x7e, 0x00, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0x40, 0xfd, 0xf8, 0x00, 0x7e, 0xfc, 0x1f, 0xfd, 0x5e, 0x0e, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0d, 0xc0, 0xfd, 0xf8, 0x00, 0x7e, 0xfc, 0x7e, 0xff, 0x76, 0x3f, 0x1f, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0xfd, 0xf8, 0x00, 0x7e, 0xfd, 0xff, 0xaf, 0x7e, 0xff, 0xdf, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc0, 0xbd, 0xfc, 0x00, 0x5e, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xf7, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0xc3, 0xfd, 0xfe, 0x01, 0xfe, 0xff, 0xfe, 0x3f, 0x7f, 0xff, 0xff, 0xb7, 0x6e, 0x00, 
  0x00, 0x0f, 0xcf, 0xf5, 0xff, 0x87, 0xfa, 0xff, 0xfc, 0x3f, 0x7f, 0xff, 0xfe, 0xbd, 0x7a, 0x00, 
  0x00, 0x0f, 0xdf, 0xfd, 0xff, 0xef, 0xfe, 0xff, 0xf0, 0x3f, 0x7f, 0xfb, 0xff, 0xbf, 0x7e, 0x00, 
  0x00, 0x0f, 0x7f, 0xf0, 0x7f, 0xbf, 0xf8, 0x3f, 0xc0, 0x3c, 0x1f, 0xe1, 0xfe, 0x3d, 0x7a, 0x00, 
  0x00, 0x0d, 0xff, 0xe0, 0x1e, 0xff, 0xf0, 0x0f, 0x00, 0x38, 0x07, 0x80, 0x7c, 0x37, 0x6e, 0x00, 
  0x00, 0x0f, 0xff, 0x80, 0x07, 0xff, 0xc0, 0x02, 0x00, 0x20, 0x01, 0x00, 0x10, 0x3f, 0x7e, 0x00, 
  0x00, 0x07, 0xfe, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3e, 0x00, 
  0x00, 0x01, 0xf8, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x00, 
  0x00, 0x00, 0x70, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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

    if (textDisplayed == 4) {
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
    } else if (textDisplayed == 3) {
      oled.clearDisplay();
      oled.drawBitmap(0, 0, logoBitmap, 128, 64, WHITE);
      oled.display();

      textDisplayed = 4;
      lastDisplay = millis();
    }

  }
}
