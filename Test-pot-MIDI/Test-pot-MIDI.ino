// Requires Midi_Controller lib https://github.com/tttapa/MIDI_controller

#include <MIDI_Controller.h>

Analog potentiometer(A0, MIDI_CC::Channel_Volume, 1);
// Analog High Res seems to be too sensitive for Lightroom/MIDI2LR
// AnalogHiRes potentiometer(A0, 1);

void setup() {

}

void loop() {
  // Refresh the MIDI controller (check whether the potentiometer's input has changed since last time, if so, send the new value over MIDI)
  MIDI_Controller.refresh();
}