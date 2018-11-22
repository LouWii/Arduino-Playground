// The power pin needs to be a PWM pin, check your Arduino pinout
const int powerPin = 11;

// blinking delay
const int interval = 800;

int lastLedUpdate = 0;

bool onOff = false;

void setup() {
    pinMode(powerPin, OUTPUT);
}

void loop() {
    int currentTime = millis();

    if (currentTime - lastLedUpdate >= interval) {
        if (onOff) {
            onOff = false;
            // if your LED isn't bright enough, increase the value from 30 up to 255!
            analogWrite(powerPin, 30);
        } else {
            onOff = true;
            analogWrite(powerPin, 0);
        }
        lastLedUpdate = currentTime;
    }
}
