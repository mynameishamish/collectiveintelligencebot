char inChar;  // character we will use for messages from the RPi
int led = 13;


// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
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

// wrappers for the second motor!
void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}


// Now we'll wrap the 2 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{
  Serial.begin(9600);

  AFMStop.begin(); // Start the top shield

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

  // read the character we recieve on the serial port from the RPi
  if (Serial.available()) {
    inChar = (char)Serial.read();
  }






// NEW COMMANDS

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
        stepper1.moveTo(0);
        stepper1.run();
        if (stepper1.currentPosition() == 0) {
          stepper1.moveTo(15);
          stepper1.run();
          if (stepper1.currentPosition() == 15) {
            stepper1.moveTo(-15);
            stepper1.run();
            if (stepper1.currentPosition() == -15) {
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

