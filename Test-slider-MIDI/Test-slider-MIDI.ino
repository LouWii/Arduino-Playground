// Requires Midi_Controller lib https://github.com/tttapa/MIDI_controller

#include <MIDI_Controller.h>

Analog potentiometer(A0, MIDI_CC::Channel_Volume, 1);

// Instantiate a MIDI interface that sends debug messages to the USB Serial port (Serial Monitor)
USBDebugMIDI_Interface midiInterface(115200);
// Moving the slider up/down will send data over Serial
// In the serial console, you should see something like (0x0 is the minimum value, 0x7F is the max)
//  Control Change		Channel: 1	Data 1: 0x7	Data 2: 0x0
//  Control Change		Channel: 1	Data 1: 0x7	Data 2: 0x7F


void setup() {

}

void loop() {
  // Refresh the MIDI controller (check whether the potentiometer's input has changed since last time, if so, send the new value over MIDI)
  MIDI_Controller.refresh();
}
