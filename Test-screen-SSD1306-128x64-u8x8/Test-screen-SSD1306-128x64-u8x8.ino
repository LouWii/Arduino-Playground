#include <U8x8lib.h>

//U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C oled(3, 2, U8X8_PIN_NONE);

void setup() {
  oled.begin();
}

void loop() {
  oled.drawString(0,0,"Hello World!");
}
