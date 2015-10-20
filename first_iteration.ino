/*
Mechatronic Marionette
Cecilia Diehl, Elizabeth Sundsmo, Rebecca Gettys, Rebecca Patterson, Ziyu (Selina) Wang
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Initiate the motors controlling the left and right side of the body
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

const int buttonPin = 8;    // we're starting out with pin 8 being for the button
// const int motorPin1 = 13;
// const int motorPin2 = 12; // let's start with pins 11/12 being for the motor - NOTE - we could end up needing to change this later but it's easy to do

int mode = 0; // SELINA - I've left you 5 modes (0, 1, 2, 3, 4) - setting the mode happens by a button press and should cause a movement
int motor1State = 0; 
int motor2State = 0;
int currButtonState; // start off our variables - this is saying WHAT IS HAPPENING WITH THE BUTTON NOW (high/low)
int preButtonState; //
long lastTimeDebounce = 0; // when did we last change the outputs
long debounceDelay = 100; // let's make this a decent delay
unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;

void setup() {
     pinMode(buttonPin, INPUT); // let's define inputs and outputs here
    // pinMode(motorPin1, OUTPUT); 
    // pinMode(motorPin2, OUTPUT);
    AFMS.begin();  // create with the default frequency 1.6KHz
    // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(150);
  rightMotor->setSpeed(150);
}

void loop() {
  int buttonRead = digitalRead(buttonPin); // what is the button doing RIGHT NOW

if (buttonRead != preButtonState) { // if the button looks pressed, then
     // reset the debouncing timer
     lastTimeDebounce = millis();
      }
  
     if ((millis() - lastTimeDebounce) > debounceDelay) { // if the time from last press has been enough
   
        if (buttonRead != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead; // then we'd like to update our button state again

 
            if (currButtonState == HIGH) {
                mode++; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                if (mode == 5) {
                  mode = 0; // reset the mode to zero if we go past our 5th mode
                }
            }
        }
     }
preButtonState = buttonRead; // so our loops behaves itself
        
        // in the ifs update motor1behave and motor2behave
        
  if (mode == 0) {  // Lifting up the right half and return to original position
      currentMillis = millis();
      if (currentMillis - previousMillis >= 500) {            // wait for half a second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 2000) {            // wait for two second
      previousMillis = currentMillis;
      rightMotor->run(FORWARD);
      leftMotor->run(RELEASE);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 500) {            // wait for half a second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 2000) {            // wait for two second
      previousMillis = currentMillis;
      rightMotor->run(BACKWARD);
      leftMotor->run(RELEASE);
    }
  }
        
 else if (mode == 1) { // Lifting up the left half and return to original position
      currentMillis = millis();
      if (currentMillis - previousMillis >= 500) {            // wait for half a second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 2000) {            // wait for two second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(FORWARD);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 500) {            // wait for half a second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      currentMillis = millis();
      if (currentMillis - previousMillis >= 2000) {            // wait for two second
      previousMillis = currentMillis;
      rightMotor->run(RELEASE);
      leftMotor->run(BACKWARD);
      }
  }
  else if (mode ==2) { // JUMP
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for two second
    previousMillis = currentMillis;
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    }
  }
  else if (mode==3) { // DANCE
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    }
  }
  else if (mode ==4) { // CLIMB
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    leftMotor->run(FORWARD);
    rightMotor->run(RELEASE);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    rightMotor->run(FORWARD);
    leftMotor->run(RELEASE);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;     
    leftMotor->run(BACKWARD);
    rightMotor->run(RELEASE);
    }
    currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {            // wait for half a second
    previousMillis = currentMillis;
    rightMotor->run(BACKWARD);
    leftMotor->run(RELEASE);
    }
  }
}
