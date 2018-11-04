# Arduino Playground

This repository contains some experiments that I made when playing with my Arduino Leonardo and some basic components (potentiometer, button, rotary encoder).

I keep all of my experiments here for my future self.

## Schematics

Just in case I forgot everything, I've included schematics for each of my experiments, as an image, but I also attached the Fritzing file as well. [Frizing](http://www.fritzing.org/) is an open source hardware initiative, and they made a really nice and [open source software](https://github.com/fritzing/fritzing-app) to create electronic schematics.

## Comparison between Arduino display libraries

I made some tests on an SSD1306 display using different libraries. Display libraries are often quite heavy and can eat up a lot of program space and RAM, and that can be a problem if your project is complex. I tried to stay consistent in my tests, with the same structure and logic.

This could probably be improved though. Creating separate tests: text test, a draw test, a bitmap test, would be better.

* Adafruit SSD1306 - Adafruit GFX: **15240 bytes** (53%) of program space used, **1614 bytes** (63%) of dynamic memory - Probably the most complete (shapes, bitmap, text, fonts...), but also the heaviest on RAM.
* Arduino-lib-oled: **11186 bytes** (38%) of program space used, **348 bytes** (13%) of dynamic memory - Can draw shapes, bitmap and text.
* SeeedOled: **8052 bytes** (28%) of program space used, **482 bytes** (18%) of dynamic memory - Only for 128x64 displays. 1 font that's not the best (too wide). Can draw bitmap and text. This would be good library if it could adapt to other screens and if the font was better. It's always possible to fork it and change it, it's a very simple lib.
* SparkFun MicroOLED: **11886 bytes** (41%) of program space used, **819 bytes** (31%) of dynamic memory - Only for 64x48px displays. I haven't even tested it much as it's already taking too much memory without my entire test. And it's not adapted to my screen anyway.
* SSD1306Ascii Wire: **7654 bytes** (26%) of program space used, **516 bytes** (20%) of dynamic memory - Text only, has 40+ fonts.
* SSD1306Ascii Avr: **6128 bytes** (21%) of program space used, **307 bytes** (11%) of dynamic memory - Text only, has 40+ fonts.
* u8g2: **17338 bytes** (60%) of program space used, **899 bytes** (35%) of dynamic memory - Can draw shapes, bitmap and text. Has a lot of [features](https://github.com/olikraus/u8g2/wiki/u8g2reference). Has a ton of different fonts with different sizes.

## Licensing

GNU GPLv3 copyright (c) LouWii