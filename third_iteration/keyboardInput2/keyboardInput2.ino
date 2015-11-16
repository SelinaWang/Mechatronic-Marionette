/*
Mechatronic Marionette
Cecilia Diehl, Elizabeth Sundsmo, Rebecca Gettys, Rebecca Patterson, Ziyu (Selina) Wang
Control Modes: Type in the mode you want (0~4) in the Serial Monitor
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Initiate the motors controlling the left and right side of the body
Adafruit_DCMotor *lefthandMotor = AFMS.getMotor(1);
Adafruit_DCMotor *righthandMotor = AFMS.getMotor(2);
Adafruit_DCMotor *leftfootMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightfootMotor = AFMS.getMotor(4);
Adafruit_DCMotor *laterallefthandMotor = AFMS.getMotor(5);
Adafruit_DCMotor *lateralrighthandMotor = AFMS.getMotor(6);
Adafruit_DCMotor *leftheadMotor = AFMS.getMotor(7);
Adafruit_DCMotor *rightheadMotor = AFMS.getMotor(8);
Adafruit_DCMotor *shoulderMotor = AFMS.getMotor(9);
Adafruit_DCMotor *bottomMotor = AFMS.getMotor(10);

int mode = 0; // 
unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int preMode = 0;
int mode0counter = 0;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
const int buttonPin1 = 8;    
const int buttonPin2 = 9;
const int buttonPin3 = 10;
const int buttonPin4 = 11;
const int buttonPin5 = 12;
int currButtonState; // start off our variables - this is saying WHAT IS HAPPENING WITH THE BUTTON NOW (high/low)
int preButtonState; //
long lastTimeDebounce = 0; // when did we last change the outputs
long debounceDelay = 100; // let's make this a decent delay
int keyboardInput;

void setup() {
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    pinMode(buttonPin3, INPUT);
    pinMode(buttonPin4, INPUT);
    pinMode(buttonPin5, INPUT);
    AFMS.begin();  // create with the default frequency 1.6KHz
    // Set the speed to start, from 0 (off) to 255 (max speed)
    lefthandMotor->setSpeed(150);
    righthandMotor->setSpeed(150);
    leftfootMotor->setSpeed(150);
    rightfootMotor->setSpeed(150);
    laterallefthandMotor->setSpeed(150);
    lateralrighthandMotor->setSpeed(150);
    leftheadMotor->setSpeed(150);
    rightheadMotor->setSpeed(150);
    shoulderMotor->setSpeed(150);
    bottomMotor->setSpeed(150);
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

  int buttonRead1 = digitalRead(buttonPin1); // what are the buttons doing RIGHT NOW
  int buttonRead2 = digitalRead(buttonPin2);
  int buttonRead3 = digitalRead(buttonPin3);
  int buttonRead4 = digitalRead(buttonPin4);
  int buttonRead5 = digitalRead(buttonPin5);


  if (buttonRead1 != preButtonState || buttonRead2 != preButtonState|| buttonRead3 != preButtonState|| buttonRead4 != preButtonState || buttonRead5 != preButtonState) { // if the button looks pressed, then
     // reset the debouncing timer
     lastTimeDebounce = millis();
      }
  if ((millis() - lastTimeDebounce) > debounceDelay) { // if the time from last press has been enough
   
        if (buttonRead1 != currButtonState || buttonRead2 != currButtonState || buttonRead3 != currButtonState|| buttonRead4 != currButtonState|| buttonRead5 != currButtonState) { // and if what the button is saying now is not equal to the current reading
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

      
  if (mode == 0) {  // Right hand wave
      if (mode0counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(FORWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      }
      }
      if (mode0counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode0counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode0counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode0counter++;
      Serial.println(mode0counter);
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode0counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode0counter = 0;
      Serial.println(mode0counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
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
      lefthandMotor->run(FORWARD);
      righthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter = 0;
      Serial.println(mode1counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      leftheadMotor->run(RELEASE);
      rightheadMotor->run(RELEASE);
      shoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
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
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode2counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(FORWARD);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode2counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter = 0;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
  }
  else if (mode==3) { // MARCH
    Serial.println("In Mode 3");
    if (mode3counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode3counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode3counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode3counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter = 0;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
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
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;   
      mode4counter++;
    lefthandMotor->run(BACKWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter = 0;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    leftheadMotor->run(RELEASE);
    rightheadMotor->run(RELEASE);
    shoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
  }
}
