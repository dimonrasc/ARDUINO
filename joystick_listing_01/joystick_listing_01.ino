
#include "Joystick.h"
Joystick_ Joystick;
 
int JoystickX;
int JoystickY;

void setup() {
  Serial.begin(9600);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 1024); 
  Joystick.setYAxisRange(0, 1024);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
 
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);

  // Read Joystick
  JoystickX = analogRead(A9); // Hall effect sensor connects to this analog pin
  JoystickY = analogRead(A8); // Hall effect sensor connects to this analog pin

  // Output Controls
  Joystick.setXAxis(JoystickX);
  Joystick.setYAxis(JoystickY);

  Joystick.sendState();
}
