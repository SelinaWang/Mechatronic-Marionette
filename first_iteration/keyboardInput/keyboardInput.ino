/*
Mechatronic Marionette
Cecilia Diehl, Elizabeth Sundsmo, Rebecca Gettys, Rebecca Patterson, Ziyu (Selina) Wang
Control Modes: Type in the mode you want (0~4) in the Serial Monitor
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
Adafruit_DCMotor *lateralleftMotor = AFMS.getMotor(3);
Adafruit_DCMotor * lateralrightMotor = AFMS.getMotor(4);

int mode = 0; // 
unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int preMode = 0;
int mode0counter = 0;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
int keyboardInput;

void setup() {
    AFMS.begin();  // create with the default frequency 1.6KHz
    // Set the speed to start, from 0 (off) to 255 (max speed)
    leftMotor->setSpeed(150);
    rightMotor->setSpeed(150);
    lateralMotor->setSpeed(150);
    Serial.begin(9600);
}

void loop() {

    // read input from keyboard
  if (Serial.available() > 0)
  {
    keyboardInput = Serial.read();
    Serial.println(keyboardInput);
    if (keyboardInput >=48 && keyboardInput <=52) {
      mode = (keyboardInput - 48);
    }
  }
   
      if (mode != preMode) { // if the mode has changed
        preMode = mode; // then we'd like to update our mode
        mode0counter = 0;
        mode1counter = 0;
        mode2counter = 0;
        mode3counter = 0;
        mode4counter = 0;
      }
  
  if (mode == 0) {  // Right hand wave
      if (mode0counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(FORWARD);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(FORWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(BACKWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      if (mode0counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(FORWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(BACKWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      if (mode0counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(FORWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(BACKWARD);
      lateralleftMotor->run(RELEASE);
      }
      }
      if (mode0counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      rightMotor->run(BACKWARD);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter = 0;
      Serial.println(mode0counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
    }

  else if (mode == 1) {  // Left hand wave
      if (mode1counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      leftMotor->run(FORWARD);
      rightMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(FORWARD);
      }
      }
      
      if (mode1counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(BACKWARD);
      }
      }
      if (mode1counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(FORWARD);
      }
      }
      
      if (mode1counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(BACKWARD);
      }
      }
      if (mode1counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(FORWARD);
      }
      }
      
      if (mode1counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
      if (mode1counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      rightMotor->run(BACKWARD);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter = 0;
      Serial.println(mode1counter);
      rightMotor->run(RELEASE);
      leftMotor->run(RELEASE);
      lateralrightMotor->run(RELEASE);
      lateralleftMotor->run(RELEASE);
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
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
    if (mode2counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter = 0;
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
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
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
    if (mode3counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter = 0;
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
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
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
    if (mode4counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    rightMotor->run(FORWARD);
    leftMotor->run(RELEASE);
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
    if (mode4counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;   
      mode4counter++;
    leftMotor->run(BACKWARD);
    rightMotor->run(RELEASE);
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
    if (mode4counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter = 0;
    rightMotor->run(BACKWARD);
    leftMotor->run(RELEASE);
    lateralrightMotor->run(RELEASE);
    lateralleftMotor->run(RELEASE);
    }
    }
  }
}
