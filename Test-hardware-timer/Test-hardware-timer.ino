
// Select the timers you're using, here ITimer1
#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false
#define USE_TIMER_4     false
#define USE_TIMER_5     false

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TimerInterrupt.h"           //https://github.com/khoih-prog/TimerInterrupt
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "ISR_Timer.h"                //https://github.com/khoih-prog/TimerInterrupt

#define TIMER_INTERVAL_MS 5000L

#define NEW_TIMER_INTERVAL_MS 1000L

#define TIME_FOR_CHANGE 30000L

long lastTimerHandler = 0;

uint8_t changed = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Arduino ready");

  // Init timer ITimer1
  ITimer1.init();

  Serial.println("ITimer1 initialized");

  // Interval in unsigned long millisecs
  if (ITimer1.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler)) {
    lastTimerHandler = millis();
    Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  } else {
    Serial.println("Can't set ITimer. Select another freq. or timer");
  }
}

void TimerHandler()
{
  long now = millis();
  Serial.print("TimerHandler at ");
  Serial.println(now);
  Serial.print("Time elapsed since last run: ");
  Serial.print(now - lastTimerHandler);
  Serial.println("ms");
  Serial.println("");

  lastTimerHandler = now;
}

void loop() {
  // Change the timer after if Arduino has been running for TIME_FOR_CHANGE ms
  if (0 == changed && millis() > TIME_FOR_CHANGE) {
    Serial.println("-- Changing timer --");
    Serial.println("");

    ITimer1.attachInterruptInterval(NEW_TIMER_INTERVAL_MS, TimerHandler);
    lastTimerHandler = millis();
    changed = 1;
  }
}
