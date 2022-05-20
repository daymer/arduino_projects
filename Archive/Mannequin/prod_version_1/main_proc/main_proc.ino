#include "misc_objects.h"
#include "pin_def.h"
#include "input.h"
#include "common_structs.h"
#include "get_drive.h"
#include "funcs.h"
#include "interruptions.h"

struct driveInfo driveOne;
struct driveInfo driveTwo;

void setup() {
   Serial.begin(9600);
  // Setting pins as OUTPUT
  // - 1 -
  pinMode(driveONEDirPin, OUTPUT);
  pinMode(driveONEStepPin, OUTPUT);
  // - 2 -
  pinMode(driveTWODirPin, OUTPUT);
  pinMode(driveTWOStepPin, OUTPUT);
  // - LEDS -
  pinMode(LED_BUILTIN, OUTPUT);

  // Initing drives
  driveOne = GetDriveInfo(1);
  driveTwo = GetDriveInfo(2);
  
  // Setting initial direction to pins
  driveOne = SetDirection(driveOne);
  driveTwo = SetDirection(driveTwo);

  Serial.println("Init is done, warming up");
  pinMode(interruptPinLeft, INPUT_PULLUP);
  pinMode(interruptPinRight, INPUT_PULLUP);

  driveOne = WarmingUp(driveOne);
  driveTwo = WarmingUp(driveTwo);

  // Setting interruptions
  Serial.println("Warming up is done, setting interruptions up");
  attachInterrupt(digitalPinToInterrupt(interruptPinLeft), FixInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinRight), FixInterrupt, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:

}
