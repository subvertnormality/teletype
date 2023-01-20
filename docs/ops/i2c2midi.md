## I2C2MIDI

i2c2midi bridges the gap between monome Teletype and external MIDI-enabled devices, using I2C:

→ It receives I2C messages from Teletype and converts them to MIDI notes, MIDI CC messages and other MIDI messages to control external devices like synths and effects.

← It receives MIDI messages from external MIDI controllers and stores the values internally, which can be requested at any time by Teletype via I2C.