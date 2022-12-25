/**
* Microscope stage controller via joysctick and Ramps 1.4
* List of hardware: Arduino Mega 2560, Ramps 1.4, A4988 stepper drivers, Joystick with B5K potentiometers 
* arduino Mega 2560 and Ramps 1.4 pin mappings https://reprap.org/mediawiki/images/3/3f/Arduinomegapololushieldschematic.png
*/
#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 40

#define X_DIR A1
#define X_STEP A0
#define X_ENABLE 38

#define Y_DIR A7
#define Y_STEP A6
#define Y_ENABLE A2

#include "A4988.h"
A4988 xStepper(MOTOR_STEPS, X_DIR, X_STEP);
A4988 yStepper(MOTOR_STEPS, Y_DIR, Y_STEP);

void setup() {
  pinMode(X_ENABLE, OUTPUT);
  digitalWrite(X_ENABLE, LOW);
  pinMode(Y_ENABLE, OUTPUT);
  digitalWrite(Y_ENABLE, LOW);
  
  xStepper.begin(RPM);
  xStepper.enable();
  yStepper.begin(RPM);
  yStepper.enable();
}

void loop() {
    delay(1000);
}
