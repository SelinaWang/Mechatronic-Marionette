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
int currButtonState; // start off our variables - this is saying WHAT IS HAPPENING WITH THE BUTTON NOW (high/low)
int preButtonState; //
long lastTimeDebounce = 0; // when did we last change the outputs
long debounceDelay = 100; // let's make this a decent delay
unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int mode0counter = 0;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
int keyboardInput;

void setup() {
     pinMode(buttonPin, INPUT); // let's define inputs and outputs here
    // pinMode(motorPin1, OUTPUT); 
    // pinMode(motorPin2, OUTPUT);
    AFMS.begin();  // create with the default frequency 1.6KHz
    // Set the speed to start, from 0 (off) to 255 (max speed)
    leftMotor->setSpeed(150);
    rightMotor->setSpeed(150);
    Serial.begin(9600);
}

void loop() {

    // read input from keyboard
  if (Serial.available() > 0)
  {
    keyboardInput = Serial.read();
    Serial.println(keyboardInput);
    mode = (keyboardInput - 48);
  }
  
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
                mode0counter = 0;
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                if (mode == 5) {
                  mode = 0; // reset the mode to zero if we go past our 5th mode
                }
            }
        }
     }
preButtonState = buttonRead; // so our loops behaves itself
//previousMillis = millis();
        
        // in the ifs update motor1behave and motor2behave
  
  if (mode == 0) {  // Lifting up the right half and return to original position
      //Serial.println("In Mode 0");
      if (mode0counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(FORWARD);
      leftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 1) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(BACKWARD);
      leftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter = 0;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      }
    }
        
 else if (mode == 1) { // Lifting up the left half and return to original position
      Serial.println("In Mode 1");
      if (mode1counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      rightMotor->run(RELEASE);
      leftMotor->run(FORWARD);
      }
      }
      if (mode1counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      }
      }
      if (mode1counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      rightMotor->run(RELEASE);
      leftMotor->run(BACKWARD);
      }
      }
      if (mode1counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      mode1counter = 0;
      }
      }
  }
  else if (mode ==2) { // JUMP
    Serial.println("In Mode 2");
    if (mode2counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
    }
    }
    if (mode2counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter = 0;
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    }
    }
  }
  else if (mode==3) { // DANCE
    Serial.println("In Mode 3");
    if (mode3counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    }
    }
    if (mode3counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter = 0;
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    }
    }
  }

  else if (mode ==4) { // CLIMB
    Serial.println("In Mode 4");
    if (mode4counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    leftMotor->run(FORWARD);
    rightMotor->run(RELEASE);
    }
    }
    if (mode4counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    rightMotor->run(FORWARD);
    leftMotor->run(RELEASE);
    }
    }
    if (mode4counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;   
      mode4counter++;
    leftMotor->run(BACKWARD);
    rightMotor->run(RELEASE);
    }
    }
    if (mode4counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter = 0;
    rightMotor->run(BACKWARD);
    leftMotor->run(RELEASE);
    }
    }
  }
}
