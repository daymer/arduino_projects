
#define driveONEDirPin 0
#define driveONEStepPin 1  

#define driveONEstepsPerRota 1600 // steps per 1 rotation
#define driveONEmmPerRota 35  // mm per 1 rotation // REQ CALIBRATION
unsigned long driveONEstepsPerMM; // steps per 1 mm
bool driveONECurrentDir;

#define driveONEdistanceMM 20 // TO GO in mm
double driveONESpeed = 1.0; // Speed in cm/sec
double driveONEExpectedWorkTime; // how long to go in sec
bool driveONEDir = true; // true = HIGH (right, out), false = LOW (left, in) // REQ CALIBRATION

unsigned long driveONEstepsTOgo;
unsigned long driveONEExpectedWorkTimeMS;
unsigned long driveONEExpectedStepDurationMS;
double driveONETimePulsPercent = 0.5; //how long to send signal, float // REQ CALIBRATION
double driveONETimePausePercent = 0.5; //pause before and after signal, float // REQ CALIBRATION
double driveONETimePulsMS;
double driveONETimePauseMS;
 
void setup() {
  // Setting pins as OUTPUT
  pinMode(driveONEDirPin, OUTPUT);
  pinMode(driveONEStepPin, OUTPUT);

  // Calculating dependant constants
  driveONEstepsPerMM = driveONEstepsPerRota / driveONEmmPerRota; // REQ CALIBRATION 45.71428!
  driveONEstepsTOgo = driveONEdistanceMM / driveONEstepsPerMM; // REQ CALIBRATION
  
  driveONEExpectedWorkTimeMS = ((driveONEdistanceMM / 10) / driveONESpeed) * 1000; // MICRO SECONDS of work of driveOne
  driveONEExpectedStepDurationMS = driveONEstepsTOgo / driveONEExpectedWorkTimeMS;
  driveONETimePulsMS = driveONEExpectedStepDurationMS * driveONETimePulsPercent;
  driveONETimePauseMS = driveONEExpectedStepDurationMS * driveONETimePausePercent;
}

void loop() {
  setDirection();
  go();
}

void setDirection() {
    // Defining direction of driveONE
  if (driveONEDir == true) {
    driveONECurrentDir = HIGH;}
  else {
    driveONECurrentDir = LOW;};
  digitalWrite(driveONEDirPin, driveONECurrentDir);
}

void go(){
  unsigned int i;

   for ( i = 0; i < driveONEstepsTOgo; i++ ){ 
    digitalWrite(driveONEStepPin, LOW);
    delay(driveONETimePauseMS / 2);
    digitalWrite(driveONEStepPin, HIGH);
    delay(driveONETimePulsMS);
    digitalWrite(driveONEStepPin, LOW);
    delay(driveONETimePauseMS / 2);
  }
  
}
