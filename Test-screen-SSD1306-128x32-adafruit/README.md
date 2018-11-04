# SSD1306 OLED screen with Arduino Leonardo/Arduino Pro Micro

To learn more on OLED display (how to wire it), check the [README](../Test-screen-SSD1306-128x64-adafruit/README.md) in the `Test-screen-SSD1306-128x64-adafruit` folder

## Code

This test uses 2 libraries from Adafruit:
* [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library) (dependency of the above one)

**NOTE:** You need to modify the `Adafruit_SSD1306.h` file that should be stored in `My Documents\Arduino\libraries\Adafruit_SSD1306`. Around line 73 of that file, there are different options for screen sizes. Make sure that `#define SSD1306_128_32` is uncommented, and the other ones are commented out.

Those libraries are quite heavy, unfortunately, but they allow you to do a lot of different things. The big downside here is the amount of dynamic memory that's used. There are other ones too, that are more optmized and use less memory.

I'm running this program on a Pro Micro. The compiler indicates 13572 bytes (47%) of program space used, 1092 bytes (42%) of dynamic memory.
