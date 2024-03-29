# Hardware Timer

Hardware timers are used when you need code to be run at a certain time, they're very precise. It's also handy to make sure some code will always run. Even when the code is stuck somewhere (`delay()`, waiting for something, etc.), the timer will always trigger and run the function it's supposed to.

## Code

The code requires 1 library:
* [TimerInterrupt](https://github.com/khoih-prog/TimerInterrupt/tree/master) by Khoi