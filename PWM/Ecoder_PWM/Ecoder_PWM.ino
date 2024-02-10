/****************************************************************************************************************************
PWM Controlled off Encoder Input, and Synchronized LED Flashing with encoder tics

MIT License

Copyright (c) 2024 Adam Vadala-Roth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_        3
#include "RP2040_PWM.h"

// Creates pwm instance
RP2040_PWM* PWM_Instance;

// Pin definitions
#define LED_PIN      LED_BUILTIN
#define PWM_PIN      28
#define ENCODER_PIN1 2 // Change these pins to match your encoder's connections
#define ENCODER_PIN2 3 // Change these pins to match your encoder's connections

// Variables
int encoderPos = 0;
int prevEncoderPos = 0;
int dutyCycle = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup started");

  // Initialize LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Assigns PWM pin with frequency of 20 KHz and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(PWM_PIN, 20000, 0);
  Serial.println("PWM instance created");
}

void loop() {
  // Read encoder position (polling)
  int newPos = readEncoder();
  if (newPos != prevEncoderPos) {
    // Encoder position has changed
    encoderPos = newPos;
    // Map encoder position to duty cycle (0-255)
    dutyCycle = constrain(encoderPos, 0, 255);
    // Update PWM duty cycle
    PWM_Instance->setPWM(PWM_PIN, 20000, dutyCycle);
    prevEncoderPos = encoderPos;

    // Flash LED in sync with encoder rotations
    digitalWrite(LED_PIN, HIGH);    // Turn the LED on
    delay(50);                       // Wait for a short period
    digitalWrite(LED_PIN, LOW);     // Turn the LED off
  }
}

int readEncoder() {
  static int state = 0;
  static int prevState = 0;
  int encoder = 0;
  
  state = digitalRead(ENCODER_PIN1);
  if (state != prevState) {
    if (digitalRead(ENCODER_PIN2) != state) {
      encoder++;
    } else {
      encoder--;
    }
    prevState = state;
  }
  
  return encoder;
}



