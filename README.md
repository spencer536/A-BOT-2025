# A-BOT-2025
Autonomous Robot controlled via Blutooth modules

I've uploaded the code for anyone attempting to connect the Arduino Bluetooth modules ; HC05 with HC06.

There's a lot of tutorials out there --but this seemed to work for me.

Steps (roughly)
- Set HC05 (master) to AT mode (HC06 only has one mode as it's a slave) --keep an eye on the baud rates (38400), and depending on the model, the RX and TX can flip.
- Use the AT commands to set HC05 to master (AT+ROLE=1) and used AT+BIND=ADDRESS to bind the transmission to the address of the HC06.
- Restart, reset baud rates, and upload the configuration code. When powered, both modules should connect.

All other code (not involving Bluetooth), is in association with a Joystick and motors (which already have many resources online).


P.S.
The CONFIG Files are for testing purposes. Specifically, the 'CONFIG_buttontester' files sends the signal of a single button to the HC06.
