// Uses Adafruit Motorshield V.2 (good documentation here: https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/overview)
// Uses AccelStepper library: http://www.airspayce.com/mikem/arduino/AccelStepper/
// The basic way this works is it 1) Sets Stepper target with "moveTo" command, followed by "run",
// each time "run" is activated stepper moves one step, so to move it the full distance, run is looped.
// This allows multiple steppers to move at once as can be seen in the 'R' or reset function.
// This is also why I have to terminate each comand with the ' ' function once it has reached its destination,
// otherwise it will keep looping



char inChar;
int led = 13;

// Libraries
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMStop = Adafruit_MotorShield();
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);


void forwardstep1() {
  myStepper1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, SINGLE);
}

void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}



AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{
  Serial.begin(9600);

  AFMStop.begin();


// Stepper values
  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(5);

  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(5);

  pinMode(13, OUTPUT);

}

void loop()
{

  if (Serial.available()) {
    inChar = (char)Serial.read();
  }






// NEW COMMANDS
// Arduino watches serialport for these characters and triggers behaviors.
// People's position is hardcoded as -50, 0, 50

// COMMANDS
// 1, 2, 3 : Look at person 1, 2 and 3 respectively (rotation)
// M, N, B : Lean forward, upright and backward respectively (tilt)
// W : Wiggle (Shake tilt back and forth), has to be exited (space key)                              <- Needs work (Slow down)
// L : Lookaround (Rotate back and forth), has to be exited (space key)                              <- Needs work (Slow down)
// A, S, D : Look around, with swooping (tilt forward and back)                                      <- Needs work (Not working currently)
// R : Reset, move everything back to 0
// ' ' (Space key) : Exit motion but hold position


    if (inChar == '1') {
      if (stepper1.distanceToGo() == 0)
      stepper1.moveTo(-50);
      stepper1.run();
      if (stepper1.currentPosition() == -50 || stepper2.currentPosition() == -50) {
        Serial.print(' ');
      }
  }

    else if (inChar == '2') {
      if (stepper1.distanceToGo() == 0)
        stepper1.moveTo(0);
        stepper1.run();
        if (stepper1.currentPosition() == 0 || stepper2.currentPosition() == 0) {
          Serial.print(' ');
      }
  }

    else if (inChar == '3') {
      if (stepper1.distanceToGo() == 0)
        stepper1.moveTo(50);
        stepper1.run();
        if (stepper1.currentPosition() == 50 || stepper2.currentPosition() == 50) {
          Serial.print(' ');
      }
  }


    else if (inChar == 'M') {
      if (stepper2.distanceToGo() == 0)
        stepper2.moveTo(25);
        stepper2.run();
        if (stepper2.currentPosition() == 25 || stepper2.currentPosition() == 25) {
          Serial.print(' ');
      }
  }

    else if (inChar == 'N') {
      if (stepper2.distanceToGo() == 0)
        stepper2.moveTo(0);
        stepper2.run();
        if (stepper2.currentPosition() == 0 || stepper2.currentPosition() == 0) {
          Serial.print(' ');
      }
  }

    else if (inChar == 'B') {
      if (stepper2.distanceToGo() == 0)
        stepper2.moveTo(-25);
        stepper2.run();
        if (stepper2.currentPosition() == -25 || stepper2.currentPosition() == -25) {
          Serial.print(' ');
      }
  }


    else if (inChar == 'W') {
       if (stepper2.distanceToGo() == 0)
        stepper2.moveTo(5);
        stepper2.run();
        if (stepper2.currentPosition() == 5){
          stepper2.moveTo(10);
          stepper2.run();
            if (stepper2.currentPosition() == 10){
               stepper2.moveTo(10);
               stepper2.run();
                 if (stepper2.currentPosition() == 5){
                    stepper2.moveTo(10);
                    stepper2.run();
                 }
            }
        }

          Serial.print(' ');
      }


      else if (inChar == 'L') {
        if (stepper1.distanceToGo() == 0)
          stepper1.moveTo(-50);
          stepper1.run();
          if (stepper1.currentPosition() == -50) {
            stepper1.moveTo(50);
            stepper1.run();
            if (stepper1.currentPosition() == 50) {
              stepper1.moveTo(-50);
              stepper1.run();
              if (stepper1.currentPosition() == -50) {
                stepper1.moveTo(0);
                stepper1.run();
                Serial.print(' ');
              }
            }
        }
    }



      else if (inChar == 'A') {
        if (stepper1.distanceToGo() == 0)

          stepper1.moveTo(-30);
          stepper1.run();
          if (stepper1.currentPosition() == -30) {

            stepper1.moveTo(30);
            stepper1.run();
            if (stepper1.currentPosition() == 30) {
              stepper1.moveTo(-30);
              stepper1.run();
              if (stepper1.currentPosition() == -30) {
                stepper1.moveTo(0);
                stepper1.run();
                Serial.print(' ');
              }
            }
        }
    }




      else if (inChar == ' ') {
  }



    else if (inChar == 'R') {
      stepper2.moveTo(0);
      stepper1.moveTo(0);
      stepper1.run();
      stepper2.run();
  }




}
