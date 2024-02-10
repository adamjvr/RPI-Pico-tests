/****************************************************************************************************************************
Combined Sketch for Blink and PWM Control
For RP2040 boards
Written by Adam Vadala-Roth 

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

void setup() {
  // Initialize LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Assigns PWM pin with frequency of 20 KHz and a duty cycle of 0%
  PWM_Instance = new RP2040_PWM(PWM_PIN, 20000, 0);
}

void loop() {
  // Blink LED
  digitalWrite(LED_PIN, HIGH);    // Turn the LED on
  delay(1000);                     // Wait for a second
  digitalWrite(LED_PIN, LOW);     // Turn the LED off
  delay(1000);                     // Wait for a second

  // Control PWM
  float frequency = 20000;
  float dutyCycle;

  delay(1000);
  dutyCycle = 90;
  PWM_Instance->setPWM(PWM_PIN, frequency, dutyCycle);

  delay(1000);
  dutyCycle = 10;
  PWM_Instance->setPWM(PWM_PIN, frequency, dutyCycle);
}
