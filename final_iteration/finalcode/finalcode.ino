/*
Mechatronic Marionette
Authors: Ziyu (Selina) Wang
Keyboard Control Mode: Type in the mode you want (1~10) in the Serial Monitor
Buttons Control Mode: Press the button corresponding to the motion (1: right hand wave, 2: bow, 3: jump, 4: march, 5: dance, 6: random)
Modes: 1: Wave, 2: bow, 3: jump, 4: march, 5: hip drop dance, 6: drop dead, 7: shopping cart dance, 8: fly, 9: sprinkler, 10: STOP
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <EasyButton.h>

// Create the motor shield object with stacking I2C addresses
Adafruit_MotorShield AFMSMotorShield1 = Adafruit_MotorShield(0x60);
Adafruit_MotorShield AFMSMotorShield2 = Adafruit_MotorShield(0x63);
//Adafruit_MotorShield AFMSMotorShield3 = Adafruit_MotorShield(0x62);

// Initiate the motors controlling the left and right side of the body
Adafruit_DCMotor *lefthandMotor = AFMSMotorShield1.getMotor(1);  // Motor 1
Adafruit_DCMotor *righthandMotor = AFMSMotorShield1.getMotor(2);  // Motor 2
Adafruit_DCMotor *leftfootMotor = AFMSMotorShield1.getMotor(3);  // Motor 3
Adafruit_DCMotor *rightfootMotor = AFMSMotorShield1.getMotor(4);  // Motor 4
Adafruit_DCMotor *laterallefthandMotor = AFMSMotorShield2.getMotor(1);  // Motor 5
Adafruit_DCMotor *lateralrighthandMotor = AFMSMotorShield2.getMotor(2);  // Motor 6
Adafruit_DCMotor *upperbodyMotor = AFMSMotorShield2.getMotor(3);  // Motor 7
Adafruit_DCMotor *bottomMotor = AFMSMotorShield2.getMotor(4);  // Motor 8
//Adafruit_DCMotor *leftshoulderMotor = AFMSMotorShield3.getMotor(1);  // Motor 9
//Adafruit_DCMotor *bottomMotor = AFMSMotorShield3.getMotor(2);  // Motor 10
//Adafruit_DCMotor *spare1Motor = AFMSMotorShield3.getMotor(3);  // Motor 11
//Adafruit_DCMotor *spare2Motor = AFMSMotorShield3.getMotor(4);  // Motor 12

unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int preMode = 10;
int mode = 10;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
int mode5counter = 0;
int mode6counter = 0;
int mode7counter = 0;
int mode8counter = 0;
int mode9counter = 0;
int mode10counter = 0;
const int buttonPin1 = 5;    
const int buttonPin2 = 6;
const int buttonPin3 = 7;
const int buttonPin4 = 8;
const int buttonPin5 = 9;
const int buttonPin6 = 10;
int keyboardInput;

//Setting up the buttons
EasyButton button1(buttonPin1);
EasyButton button2(buttonPin2);
EasyButton button3(buttonPin3);
EasyButton button4(buttonPin4);
EasyButton button5(buttonPin5);
EasyButton button6(buttonPin6);

void setup() {
    Serial.begin(9600);
    AFMSMotorShield1.begin();
    AFMSMotorShield2.begin();
    // AFMSMotorShield3.begin();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    lefthandMotor->setSpeed(150);
    righthandMotor->setSpeed(150);
    leftfootMotor->setSpeed(50);
    rightfootMotor->setSpeed(50);
    laterallefthandMotor->setSpeed(150);
    lateralrighthandMotor->setSpeed(150);
    upperbodyMotor->setSpeed(50);
    bottomMotor->setSpeed(50);
    // if analog input pin 0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(0));
}

void loop() {
    // read input from keyboard
  if (Serial.available() > 0)
  {
    keyboardInput = Serial.read();
    Serial.println(keyboardInput);
    if (keyboardInput >= 49 && keyboardInput <= 58) {
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
    mode7counter = 0;
    mode8counter = 0;
    mode9counter = 0;
    mode10counter = 0;
  }

  if (mode == 10) {
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
        // print a random number from 1 to 10
        mode = round(random(1,10));
        Serial.println(mode);
    }
  }

  if (mode == 1) {  // Right hand wave
    Serial.println("RIGHT HAND WAVE");
      if (mode1counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for half a second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 2100) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 2000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 2500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 2500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 2500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 2500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode1counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1725) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode1counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 2100) {            // wait for 3 second
      previousMillis = currentMillis;
      mode1counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
    }

  else if (mode == 2) {  // Bow
    Serial.println("BOW");
    lefthandMotor->setSpeed(50);
    righthandMotor->setSpeed(50);
    laterallefthandMotor->setSpeed(100);
    lateralrighthandMotor->setSpeed(100);
    upperbodyMotor->setSpeed(50);
    bottomMotor->setSpeed(50);
    if (mode2counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(FORWARD);
    upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode2counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1800) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode2counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 2400) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(BACKWARD);
    upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
        if (mode2counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1700) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
    upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
       if (mode2counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode2counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(RELEASE);
    upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
    bottomMotor->run(RELEASE);
    }
    }
    if (mode2counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 50) {            // wait for half a second
      previousMillis = currentMillis;
      mode2counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      lefthandMotor->setSpeed(150);
      righthandMotor->setSpeed(150);
      laterallefthandMotor->setSpeed(150);
      lateralrighthandMotor->setSpeed(150);
      upperbodyMotor->setSpeed(50);
      bottomMotor->setSpeed(50);
      }
      }
    }
        
  else if (mode ==3) { // JUMP
    Serial.println("JUMP");
    if (mode3counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
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
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(FORWARD);
    }
    }
    if (mode3counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(FORWARD);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(FORWARD);
    }
    }
    if (mode3counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode3counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
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
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
  }
  else if (mode==4) { // MARCH
    Serial.println("MARCH");
    lefthandMotor->setSpeed(150);
    righthandMotor->setSpeed(150);
    leftfootMotor->setSpeed(150);
    rightfootMotor->setSpeed(150);
    if (mode4counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 6) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 9) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 10) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 11) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode4counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode4counter == 12) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1100) {            // wait for half a second
      previousMillis = currentMillis;
      mode4counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
  }

  else if (mode ==5) { // DANCE (Hip Drop)
    Serial.println("DANCE");
    if (mode5counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode5counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(BACKWARD);
    }
    }
    if (mode5counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;   
      mode5counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(FORWARD);
    }
    }
    if (mode5counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode5counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(BACKWARD);
    }
    }
    if (mode5counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;   
      mode5counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(FORWARD);
    }
    }
    if (mode5counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;   
      mode5counter++;
    lefthandMotor->run(BACKWARD);
    righthandMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
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
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
  }

  else if (mode ==6) { // DROP DEAD
    Serial.println("DROP DEAD");
    if (mode6counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode6counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode6counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode6counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(BACKWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode6counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;   
      mode6counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode6counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode6counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode6counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for two second
      previousMillis = currentMillis;   
      mode6counter++;
      lefthandMotor->run(BACKWARD);
      righthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(FORWARD);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode6counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1500) {            // wait for two second
      previousMillis = currentMillis;
      mode6counter = 0;
      Serial.println(mode5counter);
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
    }
    }
//    if (mode6counter == 6) {
//        currentMillis = millis();
//      if (currentMillis - previousMillis > 3000) {            // wait for half a second
//      previousMillis = currentMillis;
//      mode6counter = 0;
//      Serial.println(mode5counter);
//      righthandMotor->run(RELEASE);
//      lefthandMotor->run(RELEASE);
//      rightfootMotor->run(RELEASE);
//      leftfootMotor->run(RELEASE);
//      lateralrighthandMotor->run(RELEASE);
//      laterallefthandMotor->run(RELEASE);
//      upperbodyMotor->run(RELEASE);
////    headMotor->run(RELEASE);
////    leftshoulderMotor->run(RELEASE);
//      bottomMotor->run(RELEASE);
//      mode = 10;
//      }
//      }
  }

    else if (mode==7) { // SHOPPING CART DANCE
    Serial.println("SHOPPING CART DANCE");
    if (mode7counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(RELEASE);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 2) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(FORWARD);
    lefthandMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(FORWARD);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 6) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(RELEASE);
    righthandMotor->run(BACKWARD);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(BACKWARD);
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(BACKWARD);
    laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(FORWARD);
    leftfootMotor->run(FORWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 9) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(FORWARD);
    righthandMotor->run(RELEASE);
    leftfootMotor->run(BACKWARD);
    rightfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 10) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    lefthandMotor->run(BACKWARD);
    righthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 11) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for two second
      previousMillis = currentMillis;
      mode7counter++;
    righthandMotor->run(RELEASE);
    lefthandMotor->run(BACKWARD);
    rightfootMotor->run(BACKWARD);
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
    }
    }
    if (mode7counter == 12) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for half a second
      previousMillis = currentMillis;
      mode7counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
  }

  if (mode == 8) {  // FLY
    Serial.println("FLY");
      if (mode8counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for half a second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(FORWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(FORWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode8counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 4) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for half a second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(FORWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(FORWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(FORWARD);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode8counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(BACKWARD);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode8counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode8counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
    }

      if (mode == 9) {  // SPRINKLER
    Serial.println("SPRINKLER");
      if (mode9counter == 0) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for half a second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(FORWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode9counter == 1) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 3000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(FORWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode9counter == 2) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 3) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 4) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 250) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 5) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 6) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 250) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 7) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 8) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 250) {            // wait for half a second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode9counter == 9) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 500) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(FORWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode9counter == 10) {
      currentMillis = millis();
      if (currentMillis - previousMillis > 250) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      if (mode9counter == 11) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 1000) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter++;
      righthandMotor->run(BACKWARD);
      lefthandMotor->run(BACKWARD);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(BACKWARD);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
      }
      
      if (mode9counter == 12) {
        currentMillis = millis();
      if (currentMillis - previousMillis > 300) {            // wait for 3 second
      previousMillis = currentMillis;
      mode9counter = 0;
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//      headMotor->run(RELEASE);
//      leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      mode = 10;
      }
      }
    }
    
  else if (mode == 10) {  // STOP
    Serial.println("STOP");
      if (mode10counter == 0) {
      righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
//    headMotor->run(RELEASE);
//    leftshoulderMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
      }
    }
}
