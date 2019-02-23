

const long buttonPressInterval = 50;

// These are the input pins of the Pro Micro, in the order they are on the board, in a counter-clockwise direction
const int buttonPins[18] = {1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20, 21};

int currentButtonPinIndex = 0;

unsigned long buttonPreviousTime = 0;

int allTested = -1;

void setup() {
  Serial.begin(9600);

  // Inputs
  pinMode(buttonPins[currentButtonPinIndex], INPUT_PULLUP);

  displayWaitMessage();
}

void loop() {
  unsigned long currentMillis = millis();

  if (-1 == allTested) {
    // Delay needed to make sure Serial is connected before printing anything
    delay(1000);
    displayWaitMessage();
    allTested = 0;
  }

  if (!allTested) {
    int buttonValue = digitalRead(buttonPins[currentButtonPinIndex]);

    // Debouncing is probably not needed here but...
    if (currentMillis - buttonPreviousTime >= buttonPressInterval && 0 == buttonValue) {
      buttonPreviousTime = currentMillis;
      
      // add a short delay to loop so that the computer's serial buffer is not filled as fast
      Serial.println("Input detected!");
      if ( (currentButtonPinIndex + 1) == (int) (sizeof(buttonPins) / sizeof(buttonPins[0])) ) {
        allTested = 1;
        Serial.println("-------------------------------");
        Serial.println("  All input pins were tested.");
        Serial.println("-------------------------------");
      } else {
        currentButtonPinIndex++;
        pinMode(buttonPins[currentButtonPinIndex], INPUT_PULLUP);
        displayWaitMessage();
      }
      
    }
  }
}

void displayWaitMessage() {
  Serial.println("");
  Serial.print("Waiting for INPUT LOW on pin ");
  Serial.print(buttonPins[currentButtonPinIndex]);
  Serial.println("...");
}
