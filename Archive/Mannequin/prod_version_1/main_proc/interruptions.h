// reqs interruptPinLeft & interruptPinRight to be set in pin_def.h

volatile int InterruptLeftHitCount = 0;
volatile int InterruptRightHitCount = 0;
volatile int InterruptHitCount = 0;
volatile unsigned long LastInterruptLeftHitTime = 0;
volatile unsigned long LastInterruptRightHitTime = 0;
volatile unsigned long LastInterruptHitTime = 0;

void(* resetFunc) (void) = 0; //declare reset function at address 0


bool UseInteruptSuppres = false;
int FixInterruptBehaviour = 1; // 1 = reset, 2 = sleep, 3 = fix

void FixInterrupt() {
    if (UseInteruptSuppres == true){
        if (millis() - LastInterruptLeftHitTime >= 300) {
            LastInterruptHitTime = millis();
            InterruptHitCount++;
           };
    }
    else {
         InterruptHitCount++;
    };
    if (InterruptLeftHitCount > 0) {
        if (FixInterruptBehaviour == 1) {
            resetFunc();
            }
        else if (FixInterruptBehaviour == 2) {
                 delay(99999999);}
        else {
            // do nothing
            };
    };
}

void FixInterruptLeft() {
  if (millis() - LastInterruptLeftHitTime >= 300) {
    LastInterruptLeftHitTime = millis();
    InterruptLeftHitCount++;
    };
  if (InterruptLeftHitCount > 0) {
    resetFunc();
    };
  }

void FixInterruptRight() {
  if (millis() - LastInterruptRightHitTime >= 300) {
    LastInterruptLeftHitTime = millis();
    InterruptRightHitCount++;
    };
  if (InterruptRightHitCount > 0) {
    resetFunc();
    };
  }
