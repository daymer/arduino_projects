// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to 
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>

// EG X-Y position bed driven by 2 steppers
// Alas its not possible to build an array of these with different pins for each :-(
AccelStepper stepper1(AccelStepper::FULL2WIRE, 4, 5);
AccelStepper stepper2(AccelStepper::FULL2WIRE, 6, 7);
AccelStepper stepper3(AccelStepper::FULL2WIRE, 8, 9);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

void setup() {
  Serial.begin(9600);

  // Configure each stepper

  stepper1.setMaxSpeed(200.0); // maximum speed in steps per second
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(24);
  
  stepper2.setMaxSpeed(300.0);
  stepper2.setAcceleration(100.0);
  stepper2.moveTo(1000000);
  
  stepper3.setMaxSpeed(300.0);
  stepper3.setAcceleration(100.0);
  stepper3.moveTo(1000000); 

  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
}

void loop() {
  long positions[2]; // Array of desired stepper positions
  
  positions[0] = 1000; // =17.5mm
  positions[1] = 400;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
  // Move to a different coordinate
  positions[0] = -100;
  positions[1] = 100;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
}