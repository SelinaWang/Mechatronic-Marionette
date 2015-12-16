/*
Mechatronic Marionette
Authors: Rebecca Gettys, Ziyu (Selina) Wang
Keyboard Control Mode: Type in the mode you want (1~5) in the Serial Monitor
Buttons Control Mode: Press the button corresponding to the motion (1: right hand wave, 2: left hand wave, 3: jump, 4: march, 5: dance, 6: stop)
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
//#include <Bounce2.h>
#include <EasyButton.h>
//#include <Button.h>

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMSMotorShield1 = Adafruit_MotorShield(0x60);
Adafruit_MotorShield AFMSMotorShield2 = Adafruit_MotorShield(0x61);
Adafruit_MotorShield AFMSMotorShield3 = Adafruit_MotorShield(0x62);

// Initiate the motors controlling the left and right side of the body
Adafruit_DCMotor *lefthandMotor = AFMSMotorShield1.getMotor(1);  // Motor 1
Adafruit_DCMotor *righthandMotor = AFMSMotorShield1.getMotor(2);  // Motor 2
Adafruit_DCMotor *leftfootMotor = AFMSMotorShield1.getMotor(3);  // Motor 3
Adafruit_DCMotor *rightfootMotor = AFMSMotorShield1.getMotor(4);  // Motor 4
Adafruit_DCMotor *laterallefthandMotor = AFMSMotorShield2.getMotor(1);  // Motor 5
Adafruit_DCMotor *lateralrighthandMotor = AFMSMotorShield2.getMotor(2);  // Motor 6
Adafruit_DCMotor *rightshoulderMotor = AFMSMotorShield2.getMotor(3);  // Motor 7
Adafruit_DCMotor *headMotor = AFMSMotorShield2.getMotor(4);  // Motor 8
Adafruit_DCMotor *leftshoulderMotor = AFMSMotorShield3.getMotor(1);  // Motor 9
Adafruit_DCMotor *bottomMotor = AFMSMotorShield3.getMotor(2);  // Motor 10
Adafruit_DCMotor *spare1Motor = AFMSMotorShield3.getMotor(3);  // Motor 11
Adafruit_DCMotor *spare2Motor = AFMSMotorShield3.getMotor(4);  // Motor 12

unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int preMode = 6;
int mode = 6;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
int mode5counter = 0;
int mode6counter = 0;
const int buttonPin1 = 5;    
const int buttonPin2 = 6;
const int buttonPin3 = 7;
const int buttonPin4 = 8;
const int buttonPin5 = 9;
const int buttonPin6 = 10;
//int currButton1State = 0; // start off our variables - this is saying WHAT IS HAPPENING WITH THE BUTTON NOW (high/low)
//int preButton1State = 0;
//int currButton2State = 0;
//int preButton2State = 0;
//int currButton3State = 0;
//int preButton3State = 0;
//int currButton4State = 0;
//int preButton4State = 0;
//int currButton5State = 0;
//int preButton5State = 0;
//int currButton6State = 0;
//int preButton6State = 0;
long lastTimeDebounce = 0; // when did we last change the outputs
long debounceDelay = 100; // let's make this a decent delay
int keyboardInput;

EasyButton button1(buttonPin1);
EasyButton button2(buttonPin2);
EasyButton button3(buttonPin3);
EasyButton button4(buttonPin4);
EasyButton button5(buttonPin5);
EasyButton button6(buttonPin6);

void setup() {
    AFMSMotorShield1.begin();
    AFMSMotorShield2.begin();
    AFMSMotorShield3.begin();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    lefthandMotor->setSpeed(250);
    righthandMotor->setSpeed(250);
    leftfootMotor->setSpeed(150);
    rightfootMotor->setSpeed(150);
    laterallefthandMotor->setSpeed(250);
    lateralrighthandMotor->setSpeed(250);
    rightshoulderMotor->setSpeed(150);
    headMotor->setSpeed(150);
    leftshoulderMotor->setSpeed(150);
    bottomMotor->setSpeed(150);
    Serial.begin(9600);
}

void loop() {

    // read input from keyboard
  if (Serial.available() > 0)
  {
    keyboardInput = Serial.read();
    Serial.println(keyboardInput);
    if (keyboardInput >=49 && keyboardInput <=53) {
      mode = (keyboardInput - 48);
    }
  }
   
  if (mode != preMode) { // if the mode has changed
    preMode = mode; // then we'd like to update our mode
    mode1counter = 0;
    mode2counter = 0;
    mode3counter = 0;
    mode4counter = 0;
    mode5counter = 0;
    mode6counter = 0;
  }

  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();

  if(button1.IsPushed()){
        mode = 1;
  }
  if(button2.IsPushed()){
        mode = 2;
  }
  if(button3.IsPushed()){
        mode = 3;
  }
  if(button4.IsPushed()){
        mode = 4;
  }
  if(button5.IsPushed()){
        mode = 5;
  }
  if(button6.IsPushed()){
        mode = 6;
  }

  if (mode == 1) {  // Right hand wave
    Serial.println("RIGHT HAND WAVE");
      if (mode1counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode1counter++;
      Serial.println(mode1counter);
      righthandMotor->run(FORWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
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
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 6;
      }
      }
    }

  else if (mode == 2) {  // Left hand wave
    Serial.println("LEFT HAND WAVE");
      if (mode2counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      lefthandMotor->run(FORWARD);
      righthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode2counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode2counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode2counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode2counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode2counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode2counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode2counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode2counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode2counter = 0;
      Serial.println(mode2counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 6;
      }
      }
    }
        
  else if (mode ==3) { // JUMP
    Serial.println("JUMP");
    if (mode3counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(BACKWARD);
    bottomMotor->run(BACKWARD);
    }
    }
    if (mode3counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(FORWARD);
    bottomMotor->run(FORWARD);
    }
    }
    if (mode3counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(FORWARD);
    bottomMotor->run(FORWARD);
    }
    }
    if (mode3counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(BACKWARD);
    bottomMotor->run(BACKWARD);
    }
    }
    if (mode3counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode3counter = 0;
      Serial.println(mode3counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 6;
      }
      }
  }
  else if (mode==4) { // MARCH
    Serial.println("MARCH");
    if (mode4counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode4counter = 0;
      Serial.println(mode4counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 6;
      }
      }
  }

  else if (mode ==5) { // DANCE
    Serial.println("DANCE");
    if (mode5counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(FORWARD);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(BACKWARD);
    rightshoulderMotor->run(BACKWARD);
    headMotor->run(FORWARD);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;   
      mode5counter++;
    lefthandMotor->run(BACKWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(FORWARD);
    headMotor->run(BACKWARD);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(RELEASE);
    headMotor->run(RELEASE);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(FORWARD);
    headMotor->run(BACKWARD);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;   
      mode5counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(BACKWARD);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    rightshoulderMotor->run(BACKWARD);
    headMotor->run(FORWARD);
    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 6) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode5counter = 0;
      Serial.println(mode5counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 6;
      }
      }
  }

  else if (mode == 6) {  // STOP
    Serial.println("STOP");
      if (mode6counter == 0) {
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      rightshoulderMotor->run(RELEASE);
      headMotor->run(RELEASE);
      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
    }
}
