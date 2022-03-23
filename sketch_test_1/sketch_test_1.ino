
#define driveONEDirPin 2
#define driveONEStepPin 3

#define driveONEstepsPerRota 1600 // steps per 1 rotation
#define driveONEmmPerRota 35  // mm per 1 rotation // REQ CALIBRATION

// -----INPUT----- 
#define driveONEdistanceMM 200 // TO GO in mm
double driveONESpeed = 1.0; // Speed in cm/sec
bool driveONEStartDir = true; // true = HIGH (right, out), false = LOW (left, in) // REQ CALIBRATION
// ---------------


double driveONETimePulsPercent = 0.5; //how long to send signal, float // REQ CALIBRATION
double driveONETimePausePercent = 0.5; //pause before and after signal, float // REQ CALIBRATION

int driveNum;
int driveDirPin;
int driveCurrentDir;

struct driveInfo {
  int dirPin;
  int stepPin;
  bool currentDir;
  bool startDir;
  unsigned long stepsPerMM;
  unsigned long stepsTOgo;
  unsigned long expectedWorkTimeMS;
  unsigned long expectedStepDurationMS;
  double timePulsMS;
  double timePauseMS;
  
};

struct driveInfo GetDriveInfo(int driveNum){
   // Defining driveDirPin and driveCurrentDir
   struct driveInfo _driveInfo;   
  if (driveNum == 1){
    _driveInfo.dirPin = driveONEDirPin;
    //_driveInfo.currentDir = 0;
    _driveInfo.startDir = driveONEStartDir;
    _driveInfo.stepPin = driveONEStepPin;
    
    _driveInfo.stepsPerMM = driveONEstepsPerRota / driveONEmmPerRota; // REQ CALIBRATION 45.71428!
    _driveInfo.stepsTOgo = driveONEdistanceMM / _driveInfo.stepsPerMM;
    _driveInfo.expectedWorkTimeMS = ((driveONEdistanceMM / 10) / driveONESpeed) * 1000; // MICRO SECONDS of work of driveOne
    _driveInfo.expectedStepDurationMS = _driveInfo.stepsTOgo / _driveInfo.expectedWorkTimeMS;
    _driveInfo.timePulsMS = _driveInfo.expectedStepDurationMS * driveONETimePulsPercent;
    _driveInfo.timePauseMS = _driveInfo.expectedStepDurationMS * driveONETimePausePercent;
    
    return _driveInfo;
  }
}

struct driveInfo driveONEInfo;
 
void setup() {
  // Setting pins as OUTPUT
  pinMode(driveONEDirPin, OUTPUT);
  pinMode(driveONEStepPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  driveONEInfo = GetDriveInfo(1);
  SetDirection(driveONEInfo);
}

void blinkStart(){
  unsigned int i;

   for ( i = 0; i < 5; i++ ){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
   }
}

void loop() {
  blinkStart();
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  Go(1);
  digitalWrite(LED_BUILTIN, LOW);
  ChangeDirection(driveONEInfo);
}


void SetDirection(struct driveInfo _driveInfo) {
  if (_driveInfo.startDir == true) {
    _driveInfo.currentDir = true;}
  else {
    _driveInfo.currentDir = false;};
  digitalWrite(_driveInfo.dirPin, _driveInfo.currentDir);
}

void ChangeDirection(struct driveInfo _driveInfo) {
  if (_driveInfo.currentDir == true) {
    _driveInfo.currentDir = false;}
  else {
    _driveInfo.currentDir = true;};
  digitalWrite(_driveInfo.dirPin, _driveInfo.currentDir);
}

void Go(int driveNum){
  struct driveInfo _driveInfo;
  _driveInfo = GetDriveInfo(driveNum);
  
  unsigned int i;

   for ( i = 0; i < _driveInfo.stepsTOgo; i++ ){ 
    digitalWrite(_driveInfo.stepPin, LOW);
    delay(_driveInfo.timePauseMS / 2);
    digitalWrite(_driveInfo.stepPin, HIGH);
    delay(_driveInfo.timePulsMS);
    digitalWrite(_driveInfo.stepPin, LOW);
    delay(_driveInfo.timePauseMS / 2);
  }
  
}
