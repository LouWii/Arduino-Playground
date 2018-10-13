// Requires Midi_Controller lib https://github.com/tttapa/MIDI_controller

#include <MIDI_Controller.h>

Analog potentiometer(A0, MIDI_CC::Channel_Volume, 1);

const long buttonPressInterval = 50;
const int numberOfLayers = 4;

const int LEDPIN = LED_BUILTIN;

// Layers
const int layerUpButtonPin = 2;
int layerUpButtonState = 0;
unsigned long layerUpButtonPreviousTime = 0;
int currentLayer = 0;
// Bank is from MIDI_Controller (more about banks at the bottom)
Bank bank(numberOfLayers);

void setup() {
  Serial.begin(9600);

  // Inputs
  pinMode(layerUpButtonPin, INPUT_PULLUP);

  // Led ouput
  pinMode(LEDPIN, OUTPUT);

  // Layers
  bank.add(potentiometer, Bank::CHANGE_CHANNEL);
}

void loop() {
  refreshCurrentLayer();

  // Refresh the MIDI controller (check whether the inputs have changed since last time, if so, send the new value over MIDI)
  MIDI_Controller.refresh();

  if (currentLayer % 4 == 0) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
}

/**
 * Run some logic to change the current layer if needed
 */
void refreshCurrentLayer() {
  unsigned long currentMillis = millis();
  int layerUpButtonStateCurrent = digitalRead(layerUpButtonPin);
  
  if (layerUpButtonState != layerUpButtonStateCurrent) {
    // State of the button has changed
    layerUpButtonState = layerUpButtonStateCurrent;

    // To avoid bouncing, we check the last time the button state has been pushed (LOW state)
    //  compare it to our defined interval to validate the push or not
    if (layerUpButtonStateCurrent == LOW
    && currentMillis - layerUpButtonPreviousTime >= buttonPressInterval) {
      layerUpButtonPreviousTime = currentMillis;
      currentLayer = (currentLayer + 1) % numberOfLayers;
      bank.setBankSetting(currentLayer);
      Serial.println(currentLayer);
      delay(2);
    }
  } else {

  }
  
}

/*
  ABOUT BANKS
  -----------
  When the bank setting is set to 1, 
    2 (i.e. the number of tracks per bank) will be added to the channel number of the potentiometers.
      This is because they were added to the bank using the CHANGE_CHANNEL mode.
    2 (i.e. the number of tracks per bank) will be added to the note numbers of the buttons.
      This is because they were added to the bank using the CHANGE_ADDRESS mode;
  In general:
    For controls that were added using the CHANGE_ADDRESS mode:
      The address will be: startAddress + tracksPerBank * bankSetting
      The channel won't change.
    For controls that were added using the CHANGE_CHANNEL mode:
      The channel will be: startChannel + tracksPerBank * bankSetting
      The address won't change.
*/