
#define driveONEDirPin 0
#define driveONEStepPin 1

#define driveONEstepsPerRota 1600 // steps per 1 rotation
#define driveONEmmPerRota 35  // mm per 1 rotation // REQ CALIBRATION
unsigned long driveONEstepsPerMM; // steps per 1 mm
bool driveONECurrentDir;

#define driveONEdistanceMM 20 // TO GO in mm
double driveONESpeed = 1.0; // Speed in cm/sec
double driveONEExpectedWorkTime; // how long to go in sec
bool driveONEStartDir = true; // true = HIGH (right, out), false = LOW (left, in) // REQ CALIBRATION



double driveONETimePulsPercent = 0.5; //how long to send signal, float // REQ CALIBRATION
double driveONETimePausePercent = 0.5; //pause before and after signal, float // REQ CALIBRATION
double driveONETimePulsMS;
double driveONETimePauseMS;
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
    _driveInfo.currentDir = driveONECurrentDir;
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

  // Calculating dependant constants
  // driveONEstepsPerMM = driveONEstepsPerRota / driveONEmmPerRota; // REQ CALIBRATION 45.71428!
  // driveONEstepsTOgo = driveONEdistanceMM / driveONEstepsPerMM; // REQ CALIBRATION
  
  //driveONEExpectedWorkTimeMS = ((driveONEdistanceMM / 10) / driveONESpeed) * 1000; // MICRO SECONDS of work of driveOne
  //driveONEExpectedStepDurationMS = driveONEstepsTOgo / driveONEExpectedWorkTimeMS;
  //driveONETimePulsMS = driveONEExpectedStepDurationMS * driveONETimePulsPercent;
  // driveONETimePauseMS = driveONEExpectedStepDurationMS * driveONETimePausePercent;
  
  driveONEInfo = GetDriveInfo(1);
  SetDirection(driveONEInfo);
}

void loop() {
  
  Go(1);
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
