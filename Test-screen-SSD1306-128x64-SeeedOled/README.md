# SSD1306 OLED screen with Arduino Leonardo/Arduino Pro Micro

To learn more on OLED display (how to wire it), check the [README](../Test-screen-SSD1306-128x64-adafruit/README.md) in the `Test-screen-SSD1306-128x64-adafruit` folder

## Code

This test uses 2 libraries:
* [Seeed OLED Display 128x64](https://github.com/Seeed-Studio/OLED_Display_128X64)
* [Wire (official Arduino lib)](https://www.arduino.cc/en/Reference/Wire)

This lib is only for 128x64 I2C screens. It uses `Wire` so you can't configure what pin to use. It's for text and bitmap only. It doesn't have a lot of features, has 1 font only.

I think the font is too wide and only allows for 16 chars on one line (each char is 8x8). If the line is too long, the text gets thrown out to the first line, overriding what's already displayed. That can be changed though, by modifying the lib and it doesn't look very hard.

I'm running this program on a Pro Micro. The compiler indicates 8052 bytes (28%) of program space used, 482 bytes (18%) of dynamic memory. Reasonable on the program space, ok on the dyanmic memory side.