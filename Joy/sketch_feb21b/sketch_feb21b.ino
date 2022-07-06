#include <Joystick.h>

void setup() {
  Joystick.begin();

  //pinMode(A0, INPUT_PULLUP);
  //pinMode(A1, INPUT_PULLUP);
}

void loop() {
  analogRead(0);     // Reading X axis value twice to prevent interference with Y axis (Only using second reading)
  Joystick.setXAxis(analogRead(0));
  analogRead(1);     // Reading Y axis value twice to prevent interference with X axis (Only using second reading)
  Joystick.setYAxis(analogRead(1));
  Joystick.sendState();
  delay(50);
}
