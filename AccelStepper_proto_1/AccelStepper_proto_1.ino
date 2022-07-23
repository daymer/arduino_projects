// MultiStepper.pde
// -*- mode: C++ -*-
// Use MultiStepper class to manage multiple steppers and make them all move to 
// the same position at the same time for linear 2d (or 3d) motion.

#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::FULL2WIRE, 4, 5); // body rotation
AccelStepper stepper2(AccelStepper::FULL2WIRE, 6, 7); // head rotation
AccelStepper stepper3(AccelStepper::FULL2WIRE, 8, 9); // R hand up-down
//AccelStepper stepper4(AccelStepper::FULL2WIRE, 10, 11); // R hand in-out (REQS CALIBRATION!)
AccelStepper stepper5(AccelStepper::FULL2WIRE, A0, A1); // L hand up-down
//AccelStepper stepper6(AccelStepper::FULL2WIRE, A2, A3); // L hand in-out (REQS CALIBRATION!)

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper steppers;

void setup() {
  Serial.begin(9600);

  // Configure each stepper

  stepper1.setMaxSpeed(3600.0); // maximum speed in steps per second
  stepper1.setAcceleration(400.0);
  //stepper1.moveTo(24);


  stepper2.setMaxSpeed(32000);
  stepper2.setAcceleration(8000.0);
  //stepper2.moveTo(1000000);

 
  stepper3.setMaxSpeed(600.0);
  stepper3.setAcceleration(200.0);
  //stepper3.moveTo(1000000); 

  stepper5.setMaxSpeed(600.0);
  stepper5.setAcceleration(200.0);
  


  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
  steppers.addStepper(stepper5);
}

void loop() {
  delay(5000);
  long positions[1]; // Array of desired stepper positions
  
  positions[0] = -8000; // 200
  positions[1] = 30000; // 400
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
  // Move to a different coordinate
  positions[0] = 8000;
  positions[1] = -30000;
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  //delay(1000);
}
