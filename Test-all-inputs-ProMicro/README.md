# All inputs test for Pro Micro

This test goes though all input pins on a Pro Micro to test them and make sure they are able to detect a state change.

In this test, we check for a `LOW` state, meaning you have to apply `GND` to the pin to make it detect a change.

This will only work for a Pro Micro, and maybe a Leonardo. But you can easily edit the code to make it work for any Arduino out there. All the pins are listed in an array. Just edit that array and the rest should follow.