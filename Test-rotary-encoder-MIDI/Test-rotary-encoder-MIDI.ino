// Requires Midi_Controller lib https://github.com/tttapa/MIDI_controller

#define USE_ROTARY_ENCODER
#include <MIDI_Controller.h>


/*
  This is an example of the "RotaryEncoder" class of the MIDI_controller library.
  Connect the A and B pins of the encoder to 2 interrupt pins (2 and 3). 
  It's recommended to use 100nF capacitors between the A and B pins and ground (hardware debounce).
  Connect the common (C) pin to the ground. Pull-up resistors are not necessary, since the internal ones will be used.
  Map the control change message 0x14 to the right control in your DJ or DAW software, 
  and select 'relative' instead of 'absolute'.
  If you are using a jog wheel, use JOG, if you are using a normal encoder 
  (for normal controls like EQ or volume etc.) use NORMAL_ENCODER.
  If you have strange results in your software, try a different relative mode: 
  TWOS_COMPLEMENT, BINARY_OFFSET or SIGN_MAGNITUDE.
  If the control works, but it goes in the wrong direction, swap the pins A and B of the encoder 
  (either physically, or by swapping the pin numbers in the RotaryEncoder constructor).
  Written by Pieter P, 22-08-2017
  https://github.com/tttapa/MIDI_controller
*/

/*
  In MIDI2LR, we need to change the settings of the row otherwise rotary encoders don't work properly.
  Right click on the row LR Command button to make the settings popup show up
  Check "Two's complement"
  The definition depends on the slider you want to control
  For instance, Exposure, with definition set to 400, will move the slider 0.05 by 0.05 (200: 0.10 by 0.10)
  Blacks, with definition set to 200, will move the slider 2 by 2 (400: 1 by 1)
  You might want to change it depending on the rotary encoder as well (some have more/less steps)
*/


const uint8_t Channel = 1;       // MIDI channel 1
const uint8_t Controller = 0x14; // MIDI Control Change controller number https://www.midi.org/specifications/item/table-3-control-change-messages-data-bytes-2
const int speedMultiply = 1; // No change in speed of the encoder (number of steps is multiplied by 1)

RotaryEncoder encoder(1, 0, Controller, Channel, speedMultiply, NORMAL_ENCODER, TWOS_COMPLEMENT);

// Instantiate a MIDI interface that sends debug messages to the USB Serial port (Serial Monitor)
//USBDebugMIDI_Interface midiInterface(115200);

void setup() {}

void loop() {
  // Refresh the encoder (check whether the position has changed since last time, if so, send the difference over MIDI)
  MIDI_Controller.refresh();
}
