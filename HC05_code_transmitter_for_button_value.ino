#include <SoftwareSerial.h>
SoftwareSerial BT(11,10); // RX, TX (Arduino -> HC-05)

int buttonPin = 2;  

void setup() {
  BT.begin(9600);      // HC-05 in data mode (fast blinking), 38400 for AT mode
  Serial.begin(9600);  // Optional: for debugging
  pinMode(buttonPin,INPUT);
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);
    // INPUT_PULLUP logic: pressed = LOW
  if (buttonState == LOW) {
    BT.write('1');
    Serial.print('1');
  } else {
    BT.write('0');
    Serial.print('0');
  }
  
  

  delay(200); // limit spam

  
}


