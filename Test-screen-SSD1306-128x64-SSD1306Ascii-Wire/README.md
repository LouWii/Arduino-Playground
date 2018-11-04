# SSD1306 OLED screen with Arduino Leonardo/Arduino Pro Micro

To learn more on OLED display (how to wire it), check the [README](../Test-screen-SSD1306-128x64-adafruit/README.md) in the `Test-screen-SSD1306-128x64-adafruit` folder

## Code

This test uses 1 library:
* [SSD1306Ascii](https://github.com/greiman/SSD1306Ascii)

This library is for text only. It has a lot of different fonts and nice utility functions for text operations, but it won't be able to draw anything. The lib is using a small amount of memory though.

For I2C, there are 2 implementations possible, one with `Wire` and one with `AvrI2c`. The second one is the one that uses the less memory. I'm not sure what's the difference between the two though.

In this example we're using `Wire`.

I'm running this program on a Pro Micro. The compiler indicates 7654 bytes (26%) of program space used, 516 bytes (20%) of dynamic memory. This is a bit much on the dynamic memory side. It's because of `Wire`, using the other implementation is better.