/*
   AccelStepperI2C Stepper and Servo demo
   (c) juh 2022

   This is a combination of the stepper bounce and servo sweep examples to
   demonstrate how steppers and servos can be used together.
   Attach two servos and a stepstick (A4988 etc.) driven stepper to the slave
   pins defined below.
   Of course, the slave's firmware needs to be compiled with SERVO_SUPPORT enabled.
*/

#include <Wire.h>
#include <AccelStepperI2C.h>
#include <ServoI2C.h>

uint8_t i2cAddress = 0x08;
const uint8_t stepPin = 6;
const uint8_t dirPin = 3;
const uint8_t enablePin = 8;
const uint8_t servo1Pin = 12;
const uint8_t servo2Pin = 13;

I2Cwrapper wrapper(i2cAddress); // one wrapper to serve them all
AccelStepperI2C stepper(&wrapper);
ServoI2C servo1(&wrapper);
ServoI2C servo2(&wrapper);

void setup()
{
  Wire.begin();
  // Wire.setClock(10000); // uncomment for ESP8266 slaves, to be on the safe side
  // Serial.begin(115200); // uncomment for debugging output (needs DEBUG set in libraries)

  wrapper.reset(); // reset the slave device
  delay(500); // and give it time to reboot

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  stepper.attach(AccelStepper::DRIVER, stepPin, dirPin);
  if (stepper.myNum < 0) { // stepper could not be allocated (should not happen after a reset)
    while (true) {}
  }

  // adapt the following to your board/setup, this is for CNC v3 shields with stepstick drivers:
  stepper.setEnablePin(enablePin);
  stepper.setPinsInverted(false, false, true); // directionInvert, stepInvert, enableInvert
  stepper.enableOutputs();

  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(200);
  stepper.setAcceleration(100);
  stepper.moveTo(5000); // set first target

}


int servo1pos = 90, servo2pos = 90;
int servo1speed = 11, servo2speed = 5;

void loop()
{
  
  stepper.runState(); // (re)start the state machine with the set target and parameters
  while (stepper.isRunning()) { // repeat until stepper target has been reached

    // sweep servo 1
    servo1.write(servo1pos);
    servo1pos += servo1speed;
    if (servo1pos > 180 or servo1pos < 0) {
      servo1pos -= servo1speed; // correct overshoot
      servo1speed = -servo1speed; // turn around
    }

    // sweep servo 2
    servo2.write(servo2pos);
    servo2pos += servo2speed;
    if (servo2pos > 180 or servo2pos < 0) {
      servo2pos -= servo2speed; // correct overshoot
      servo2speed = -servo2speed; // turn around
    }

    delay(50);

  }
  
  stepper.moveTo(-stepper.currentPosition()); // turn around
  
}
