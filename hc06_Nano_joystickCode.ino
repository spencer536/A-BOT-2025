#include <SoftwareSerial.h>
#include <math.h>
SoftwareSerial BT(10, 11);

int joystickbuttonLED = 3; //indicator of 
int xVal = 0;
int yVal = 0;
int buttonState = 1;
int speedValue = 0;
int positionValue;

int motorLpin1 = 8;
int motorLpin2 = 7;
int motorRpin1 = 6;
int motorRpin2 = 5;

int motorLEna = 4;
int motorREna = 9;

int deadzone = 50;  // range around center treated as neutral
int center = 511;  

void setup() {
  Serial.begin(9600);   // monitor incoming data
  BT.begin(9600);       // match HC-06 baud rate
  pinMode(joystickbuttonLED, OUTPUT);

  pinMode(motorLpin1, OUTPUT);
  pinMode(motorLpin2, OUTPUT);
  pinMode(motorRpin1, OUTPUT);
  pinMode(motorRpin2, OUTPUT);

  pinMode(motorLEna, OUTPUT);
  pinMode(motorREna, OUTPUT);

  digitalWrite(motorLpin1, LOW);
  digitalWrite(motorLpin2, LOW);
  digitalWrite(motorRpin1, LOW);
  digitalWrite(motorRpin2, LOW);
}

void loop() {
  // determine Joystick's xVal + yVal
  if (BT.available()) {
    String dataString = BT.readStringUntil('\n'); //read one line
    Serial.print(dataString);
    Serial.print('\n');

    int firstBreak = dataString.indexOf('|');
    int secondBreak = dataString.lastIndexOf('|');

    xVal = dataString.substring(0,firstBreak).toInt();
    yVal = dataString.substring(firstBreak+1,secondBreak).toInt();
    buttonState = dataString.substring(secondBreak+1).toInt(); // 1 usually (unclicked), 0 when pressed --not LOW/HIGH values (or rather they're interchangable)
    //Serial.print(buttonState);
    //Serial.print("\n");
  }

  //determine Joystick's buttonState
  if (buttonState == 0) digitalWrite(joystickbuttonLED, HIGH); //1 HIGH, 0 LOW
  else if (buttonState ==1) digitalWrite(joystickbuttonLED, LOW);

  // determine speed
  positionValue =  abs(xVal-511) + abs(yVal-511);
  //speedValue = map(positionValue,0,1024, 0,200); //motor speed from 0-255
  speedValue = 150;
  analogWrite(motorLEna, speedValue+55);  
  analogWrite(motorREna, speedValue+55);
  Serial.println(String(xVal) + "|" + String(yVal) + "|" + String(speedValue+55));

  // will be jumbled based on direction of my joystick!!!
  if (xVal == 0 && yVal ==0){
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, LOW);
  }
  else if (yVal > center + deadzone) {
    // Forward
    //Serial.println("Forward");
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, HIGH);
    digitalWrite(motorRpin1, HIGH);
    digitalWrite(motorRpin2, LOW);
  } 
  else if (yVal < center - deadzone) {
    // Backward
    //Serial.println("Backward");
    digitalWrite(motorLpin1, HIGH);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, HIGH);
  } 
  else if (xVal > center + deadzone && abs(yVal - center) <= deadzone) {
    // Rotate Right
    //Serial.println("Rotate Right");
    digitalWrite(motorLpin1, HIGH);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, HIGH);
    digitalWrite(motorRpin2, LOW);
  } 
  else if (xVal < center - deadzone && abs(yVal - center) <= deadzone) {
    // Rotate Left
    //Serial.println("Rotate Left");
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, HIGH);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, HIGH);
  } 
  
  else {
    // Nothing / Centered
    //Serial.println("Nothing");
    digitalWrite(motorLpin1, LOW);
    digitalWrite(motorLpin2, LOW);
    digitalWrite(motorRpin1, LOW);
    digitalWrite(motorRpin2, LOW);
  }


}
