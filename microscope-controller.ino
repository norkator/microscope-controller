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

#define JS_X A3
#define JS_Y A4

static int X_ZERO = 513; // raw output value when stick X is at neutral position
static int Y_ZERO = 478; // raw output value when stick Y is at neutral position
static int XY_EC = 20; // + - range which is ignored

#include "A4988.h"
A4988 xStepper(MOTOR_STEPS, X_DIR, X_STEP);
A4988 yStepper(MOTOR_STEPS, Y_DIR, Y_STEP);

void setup() {
  Serial.begin(9600);

  pinMode(X_ENABLE, OUTPUT);
  pinMode(Y_ENABLE, OUTPUT);
  
  xStepper.begin(RPM);
  xStepper.enable();
  yStepper.begin(RPM);
  yStepper.enable();

  xStepper.setMicrostep(8); // set microstep mode to 1:8
  yStepper.setMicrostep(8); // set microstep mode to 1:8
}

void loop() {
    // delay(500);
    int jsXValue = analogRead(JS_X);
    int jsYValue = analogRead(JS_Y);

    int moveX = (jsXValue - X_ZERO);
    int moveY = (jsYValue - Y_ZERO);


    // added else if so that only one axis can be moved at once
    // this is because cannot really run them same time in sync perfectly
    if (moveX > XY_EC || moveX < -XY_EC) {
      enableSteppers();
      xStepper.setRPM(abs(moveX));
      xStepper.move(moveX);
    } else if (moveY > XY_EC || moveY < -XY_EC) {
      enableSteppers();
      yStepper.setRPM(abs(moveY));
      yStepper.move(moveY);
    } else {
      disableSteppers(); // we want to be able to use stage manual adjusters normally too
    }
    
    // Serial.print("X: ");
    // Serial.print(moveX);
    // Serial.print(" ");
    // Serial.print("Y: ");
    // Serial.println(moveY);
}


void enableSteppers() {
  digitalWrite(X_ENABLE, LOW);
  digitalWrite(Y_ENABLE, LOW);
}

void disableSteppers() {
  digitalWrite(X_ENABLE, HIGH);
  digitalWrite(Y_ENABLE, HIGH);
}
