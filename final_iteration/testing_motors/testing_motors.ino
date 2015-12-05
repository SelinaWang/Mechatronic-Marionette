
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <EasyButton.h>

// Create the motor shield object with stacking I2C addresses
Adafruit_MotorShield AFMSMotorShield1 = Adafruit_MotorShield(0x60);
Adafruit_MotorShield AFMSMotorShield2 = Adafruit_MotorShield(0x61);
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
//int preMode = 10;
int mode = 10;
//int mode1counter = 0;
//int mode2counter = 0;
//int mode3counter = 0;
//int mode4counter = 0;
//int mode5counter = 0;
//int mode6counter = 0;
//int mode7counter = 0;
//int mode8counter = 0;
//int mode9counter = 0;
//int mode10counter = 0;
//const int buttonPin1 = 5;    
//const int buttonPin2 = 6;
//const int buttonPin3 = 7;
//const int buttonPin4 = 8;
//const int buttonPin5 = 9;
//const int buttonPin6 = 10;
int keyboardInput;

////Setting up the buttons
//EasyButton button1(buttonPin1);
//EasyButton button2(buttonPin2);
//EasyButton button3(buttonPin3);
//EasyButton button4(buttonPin4);
//EasyButton button5(buttonPin5);
//EasyButton button6(buttonPin6);

void setup() {
    Serial.begin(9600);
    AFMSMotorShield1.begin();
    AFMSMotorShield2.begin();
    // AFMSMotorShield3.begin();
    // Set the speed to start, from 0 (off) to 255 (max speed)
    lefthandMotor->setSpeed(50);
    righthandMotor->setSpeed(50);
    leftfootMotor->setSpeed(50);
    rightfootMotor->setSpeed(50);
    laterallefthandMotor->setSpeed(50);
    lateralrighthandMotor->setSpeed(50);
    upperbodyMotor->setSpeed(50);
    bottomMotor->setSpeed(50);
    // if analog input pin 0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
//    randomSeed(analogRead(0));
}

void loop() {
    // read input from keyboard
  if (Serial.available() > 0)
  {
    keyboardInput = Serial.read();
    Serial.println(keyboardInput);
    if (keyboardInput >= 49 && keyboardInput <= 57) {
      mode = (keyboardInput - 48);
    }
  }

  if (mode==1) {
    righthandMotor->run(FORWARD);
  }
  if (mode==2) {
    righthandMotor->run(RELEASE);
    lefthandMotor->run(FORWARD);
  }
  if (mode==3) {
    lefthandMotor->run(RELEASE);
    rightfootMotor->run(FORWARD);
  }
  if (mode==4) {
    rightfootMotor->run(RELEASE);
    leftfootMotor->run(FORWARD);
  }
  if (mode==5) {
    leftfootMotor->run(RELEASE);
    lateralrighthandMotor->run(FORWARD);
  }
  if (mode==6) {
    lateralrighthandMotor->run(RELEASE);
    laterallefthandMotor->run(FORWARD);
  }
  if (mode==7) {
    laterallefthandMotor->run(RELEASE);
    upperbodyMotor->run(FORWARD);
  }
  if (mode==8) {
    upperbodyMotor->run(RELEASE);
    bottomMotor->run(FORWARD);
  }
  if (mode==9) {
    righthandMotor->run(RELEASE);
      lefthandMotor->run(RELEASE);
      rightfootMotor->run(RELEASE);
      leftfootMotor->run(RELEASE);
      lateralrighthandMotor->run(RELEASE);
      laterallefthandMotor->run(RELEASE);
      upperbodyMotor->run(RELEASE);
      bottomMotor->run(RELEASE);
  }
}
