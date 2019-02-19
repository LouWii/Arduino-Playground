# SSD1306 OLED screen with Arduino Leonardo/Arduino Pro Micro

To learn more on OLED display (how to wire it), check the [README](../Test-screen-SSD1306-128x64-adafruit/README.md) in the `Test-screen-SSD1306-128x64-adafruit` folder

## Code

This test uses 2 libraries:
* [SparkFun Micro OLED Arduino Library](https://github.com/sparkfun/SparkFun_Micro_OLED_Arduino_Library)
* [Wire Library (official Arduino lib)](https://www.arduino.cc/en/Reference/Wire) (dependency of the one above, allows to communicate with I2C devices)

The Sparkfun Library is quite heavy, unfortunately, and it's very limited because of its un-changeable display size (**64x48px**). I didn't take the time to create my own program here, I just took the example one and modified it a bit. I don't recommend using this lib, there are other ones that are better and more optimized.

I'm running this program on a Pro Micro. The compiler indicates 11886 bytes (41%) of program space used, 819 bytes (31%) of dynamic memory. The logoBitmap variable takes 1130 bytes of program space on its own (14110 bytes (49%) without it).