## i2c2midi

i2c2midi is a DIY open source 2 HP Teletype Expander that speaks I2C and MIDI. It bridges the gap between monome Teletype and external MIDI-enabled devices, using I2C: It receives I2C messages from Teletype and converts them to MIDI notes, MIDI CC messages and other MIDI messages to control external devices like synths and effects; it receives MIDI messages from external MIDI controllers and stores the values internally, which can be requested at any time by Teletype via I2C. For more information: https://github.com/attowatt/i2c2midi
