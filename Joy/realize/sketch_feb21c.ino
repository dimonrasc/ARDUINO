
//#include "MPU6050_tockn.h"
//#include <Wire.h>
#include "Joystick.h"

//MPU6050 mpu6050(Wire);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
4, 0,                  // Button Count, Hat Switch Count
true, true, true,     // X and Y and Z Axis
false, false, false,   // No Rx, Ry, or Rz
false, false,          // No rudder or throttle
false, false, false);  // No accelerator, brake, or steering

// Constant that maps the physical pin to the joystick button.
const int pinToButtonMap = 4;
const int pinToButtonMap1 = 5;
const int pinToButtonMap2 = 6;
const int pinToButtonMap3 = 7;

void setup() {
  // Initialize Button Pins
	pinMode(pinToButtonMap, INPUT_PULLUP);
  pinMode(pinToButtonMap1, INPUT_PULLUP);
  pinMode(pinToButtonMap2, INPUT_PULLUP);
  pinMode(pinToButtonMap3, INPUT_PULLUP);

  Joystick.begin();
  Serial.begin(9600);
  //Wire.begin();
  //mpu6050.begin();

  Joystick.setXAxisRange(160, 860);
  Joystick.setYAxisRange(860, 160);
  Joystick.setZAxisRange(160, 860);


  //mpu6050.calcGyroOffsets(true);
}

// Last state of the button
int lastButtonState = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;

void loop() {
  //mpu6050.update();
  //Serial.print("angleX : ");
  //Serial.print(mpu6050.getAngleX());
  //Serial.print("\tangleY : ");
  //Serial.print(mpu6050.getAngleY());
  //Serial.print("\tangleZ : ");
  //Serial.println(mpu6050.getAngleZ());
  //Joystick.setXAxis(mpu6050.getAngleX());

  Serial.print("angleX : ");
  Serial.println(analogRead(2));    // Reading X axis value twice to prevent interference with Y axis (Only using second reading)
  Joystick.setXAxis(analogRead(2));
  Serial.print("angleY : ");
  Serial.println(analogRead(1));    // Reading Y axis value twice to prevent interference with Y axis (Only using second reading)
  Joystick.setYAxis(analogRead(1));
  Serial.print("angleZ : ");
  Serial.println(analogRead(0));    // Reading Z axis value twice to prevent interference with Y axis (Only using second reading)
  Joystick.setZAxis(analogRead(0));
  Joystick.sendState();

  // Read pin values
	int currentButtonState = digitalRead(pinToButtonMap);
	if (currentButtonState != lastButtonState)
	{
	  Joystick.setButton(0, currentButtonState);
	  lastButtonState = currentButtonState;
	}
  // Read pin values
	int currentButtonState1 = digitalRead(pinToButtonMap1);
	if (currentButtonState1 != lastButtonState1)
	{
	  Joystick.setButton(1, currentButtonState1);
	  lastButtonState1 = currentButtonState1;
	}
  // Read pin values
	int currentButtonState2 = !digitalRead(pinToButtonMap2);
	if (currentButtonState2 != lastButtonState2)
	{
	  Joystick.setButton(2, currentButtonState2);
	  lastButtonState2 = currentButtonState2;
	}
   // Read pin values
	int currentButtonState3 = !digitalRead(pinToButtonMap3);
	if (currentButtonState3 != lastButtonState3)
	{
	  Joystick.setButton(3, currentButtonState3);
	  lastButtonState3 = currentButtonState3;
	}

  delay(10);
}
