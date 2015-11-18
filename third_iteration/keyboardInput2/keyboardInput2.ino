/*
Mechatronic Marionette
Cecilia Diehl, Elizabeth Sundsmo, Rebecca Gettys, Rebecca Patterson, Ziyu (Selina) Wang
Control Modes: Type in the mode you want (1~5) in the Serial Monitor
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
// Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMSMotorShield1 = Adafruit_MotorShield(0x60);
Adafruit_MotorShield AFMSMotorShield2 = Adafruit_MotorShield(0x61);
Adafruit_MotorShield AFMSMotorShield3 = Adafruit_MotorShield(0x62);

// Initiate the motors controlling the left and right side of the body
Adafruit_DCMotor *lefthandMotor = AFMSMotorShield1.getMotor(1);
Adafruit_DCMotor *righthandMotor = AFMSMotorShield1.getMotor(2);
Adafruit_DCMotor *leftfootMotor = AFMSMotorShield1.getMotor(3);
Adafruit_DCMotor *rightfootMotor = AFMSMotorShield1.getMotor(4);
Adafruit_DCMotor *laterallefthandMotor = AFMSMotorShield2.getMotor(1);
Adafruit_DCMotor *lateralrighthandMotor = AFMSMotorShield2.getMotor(2);
Adafruit_DCMotor *rightshoulderMotor = AFMSMotorShield2.getMotor(3);
Adafruit_DCMotor *headMotor = AFMSMotorShield2.getMotor(4);
Adafruit_DCMotor *leftshoulderMotor = AFMSMotorShield3.getMotor(1);
Adafruit_DCMotor *bottomMotor = AFMSMotorShield3.getMotor(2);
Adafruit_DCMotor *spare1Motor = AFMSMotorShield3.getMotor(3);
Adafruit_DCMotor *spare2Motor = AFMSMotorShield3.getMotor(4);

int mode = 2; // 
unsigned long currentMillis = 0; // Millis used to determine how long each motion is
unsigned long previousMillis = 0;
int preMode = 0;
int mode1counter = 0;
int mode2counter = 0;
int mode3counter = 0;
int mode4counter = 0;
int mode5counter = 0;
int mode6counter = 0;
const int buttonPin1 = 0;    
const int buttonPin2 = 1;
const int buttonPin3 = 2;
const int buttonPin4 = 3;
const int buttonPin5 = 4;
const int buttonPin6 = 5;
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
    pinMode(buttonPin6, INPUT);
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

  int buttonRead1 = digitalRead(buttonPin1); // what are the buttons doing RIGHT NOW
  int buttonRead2 = digitalRead(buttonPin2);
  int buttonRead3 = digitalRead(buttonPin3);
  int buttonRead4 = digitalRead(buttonPin4);
  int buttonRead5 = digitalRead(buttonPin5);
  int buttonRead6 = digitalRead(buttonPin6);


  if (buttonRead1 != preButtonState || buttonRead2 != preButtonState|| buttonRead3 != preButtonState|| buttonRead4 != preButtonState || buttonRead5 != preButtonState || buttonRead6 != preButtonState) { // if the button looks pressed, then
     // reset the debouncing timer
     lastTimeDebounce = millis();
      }
  if ((millis() - lastTimeDebounce) > debounceDelay) { // if the time from last press has been enough
        // Check to see which button is pressed and change the mode accordingly
        if (buttonRead1 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead1; // then we'd like to update our button state again
            if (currButtonState == HIGH) {
                mode = 1; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
        else if (buttonRead2 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead2; // then we'd like to update our button state again
            if (currButtonState == HIGH) {
                mode = 2; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
        else if (buttonRead3 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead3; // then we'd like to update our button state again
            if (currButtonState == HIGH) {
                mode = 3; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
        else if (buttonRead4 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead4; // then we'd like to update our button state again
            if (currButtonState == HIGH) {
                mode = 4; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
        else if (buttonRead5 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead5; // then we'd like to update our button state again 
            if (currButtonState == HIGH) {
                mode = 5; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
        else if (buttonRead6 != currButtonState) { // and if what the button is saying now is not equal to the current reading
        currButtonState = buttonRead6 ; // then we'd like to update our button state again 
            if (currButtonState == HIGH) {
                mode = 6; // if the button is PRESSED NOW, then we would like to CHANGE MODES
                mode1counter = 0;
                mode2counter = 0;
                mode3counter = 0;
                mode4counter = 0;
                mode5counter = 0;
                mode6counter = 0;
            }
        }
     }
  preButtonState = currButtonState; // so our loops behaves itself

      
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
      mode3counter = 0;
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
      mode4counter = 0;
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
      mode5counter = 0;
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
  }

  else if (mode == 6) {  // STOP
      if (mode6counter == 0) {
      Serial.println(mode6counter);
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
