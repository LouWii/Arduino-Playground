# Arduino Modules

**Note:** Although it's sometime possible to use the chip directly on a breadboard, I've focused on breakout boards only here. Breakout boards are a bit more expensive (sometimes not by much) but are way easier to use.

**About libraries:** I'm not listing all libraries available for each module, just random ones I found. Use the *Library Manager* in Arduino IDE to help you find more libs.

## I/O Expanders

Arduinos have a limited amount of pins, and sometimes they are not enough, especially an small boards like the Pro Micro.

I/O expanders allow you to add more pins to the Arduino (12, 16 and more), while needing only 2 or 3 on the arduino itself.

### SX1509

[Example on Sparkfun](https://learn.sparkfun.com/tutorials/sx1509-io-expander-breakout-hookup-guide/all)

* I2C interface
* 16 channels (digital in/out) and **PWM**
* Not that cheap ($4-5)
* 3.3V (GPIO are 5V tolerant)
* 4 possible addresses (*0x3E*, *0x3F*, *0x70*, *0x71*) - depends on the breakout board

#### Libraries

* [SparkFun_SX1509_Arduino_Library](https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library) - Requires [*Wire*](http://www.arduino.cc/en/Reference/Wire) library for I2C. Uses *4458 bytes* of program storage space (15% on a Leonardo).

### PCF8574 / PCF8575 / PCF8575C

* I2C interface
* PCF8574 8 channels, PCF8575/PCF8575C 16 channels
* $2-3
* 5V max
* address *0x20* (some breakout boards allow to change it)

[Sparkfun PCF8575 breakout board repo (with schematics, firmware...)](https://github.com/sparkfun/I2C_Expander_Breakout-PCF8575/tree/V_H1.0_F1.0) - Sparkfun recommends the SX1509 as a replacement

PCF8575 and PCF8575C are very similar. Not sure if libraries can be used for both. PCF8575C seems to be a bit rare on breakout boards.

#### Libraries

* [pcf8574_arduino_library from skywodd for PCF8574 / PCF8575](https://github.com/skywodd/pcf8574_arduino_library)
* [PCF8575C ](https://github.com/4-20ma/I2cDiscreteIoExpander) - Requires [*Wire*](http://www.arduino.cc/en/Reference/Wire) library for I2C. Uses *4960 bytes* of program storage space

### MCP23017

* I2C interface
* 16 channels
* crazy cheap $1
* 5.5V max
* address *0x20*

#### Libraries

* [adafruit library for MCP23017](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library) - Requires [*Wire*](http://www.arduino.cc/en/Reference/Wire) library for I2C. Uses *4442 bytes* of program storage space
* [arduino-mcp23017](https://github.com/blemasle/arduino-mcp23017) - Requires [*Wire*](http://www.arduino.cc/en/Reference/Wire) library for I2C. Uses *4458 bytes* of program storage space