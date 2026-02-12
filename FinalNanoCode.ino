#include <SoftwareSerial.h>

// HC-06 connection pins
SoftwareSerial BT(10, 11); // RX, TX

int ledPin = 3; // optional: LED to visualize button state

bool connected = false;

void setup() {
  Serial.begin(9600);   // monitor incoming data
  BT.begin(9600);       // match HC-06 baud rate
  pinMode(ledPin, OUTPUT);
  Serial.println("Receiver ready...");
}

void loop() {
  if (BT.available()) {
    char c = BT.read();       // read incoming byte
    Serial.write(c);          // print to Serial Monitor

    if (!connected) {
      Serial.println("Connected!");
      connected = true;
    }

    
    // Update LED or output based on button state
    if (c == '0') digitalWrite(ledPin, LOW);   // button pressed
    if (c == '1') digitalWrite(ledPin, HIGH);  // button not pressed
  }
}