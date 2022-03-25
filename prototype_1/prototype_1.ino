
#define driveONEDirPin 2 //0
#define driveONEStepPin 3  //1
unsigned int LoopCounter;
// left d4 +
// right d5 +

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

int driveONEstepsPerRota = 200; // steps per 1 rotation
double driveONEmmPerRota = 3.5; // mm per 1 rotation // REQ CALIBRATION

// -----INPUT----- 
double driveONEdistanceMM = 100; // TO GO in mm
double driveONESpeed = 17.0; // Speed in mm/sec
bool driveONEStartDir = true; // true = HIGH (left, in), false = LOW (right, out) // REQ CALIBRATION
// ---------------

// -----Modes-----
#define PulsCalcMode 2

// PulsCalcMode 1: calc puls\pause by percent
double driveONETimePulsPercent = 0.4; //how long to send signal, float // REQ CALIBRATION
double driveONETimePausePercent = 1 - driveONETimePulsPercent; //pause before and after signal, float // REQ CALIBRATION

// PulsCalcMode 2: calc puls\pause time by fixed length
int driveONEFixedPulsTimeUS = 64; //us
// ---------------

int driveNum;

struct driveInfo {
  int dirPin;
  int stepPin;
  bool currentDir;
  bool startDir;
  double stepsPerMM;
  int stepsTOgo;
  int expectedWorkTimeMS;
  unsigned long expectedStepDurationMS;
  double timePulsMS;
  double timePauseMS;
  double selfcorrectionUS;
  
};

struct driveInfo driveOne;

struct driveInfo GetDriveInfo(int driveNum){
   // Defining driveDirPin and driveCurrentDir
  struct driveInfo _driveInfo;   
  if (driveNum == 1){
    _driveInfo.dirPin = driveONEDirPin;
    //_driveInfo.currentDir = 0;
    _driveInfo.startDir = driveONEStartDir;
    _driveInfo.stepPin = driveONEStepPin;
    
    _driveInfo.stepsPerMM = 1.0 / (driveONEmmPerRota / driveONEstepsPerRota); // REQ CALIBRATION 45.71428! #TODO: do smth with float
    _driveInfo.stepsTOgo = driveONEdistanceMM * _driveInfo.stepsPerMM;
    _driveInfo.expectedWorkTimeMS = (driveONEdistanceMM / driveONESpeed) * 1000; // MICRO SECONDS of work of driveOne
    _driveInfo.expectedStepDurationMS = _driveInfo.expectedWorkTimeMS / _driveInfo.stepsTOgo;

    if (PulsCalcMode == 1){
    
      _driveInfo.timePulsMS = _driveInfo.expectedStepDurationMS * driveONETimePulsPercent;
      _driveInfo.selfcorrectionUS = (3.50 * 2) + 50.0;
      _driveInfo.timePauseMS = (_driveInfo.expectedStepDurationMS * driveONETimePausePercent * 1000) - _driveInfo.selfcorrectionUS; 
      }
    else if (PulsCalcMode == 2){
      _driveInfo.timePulsMS = driveONEFixedPulsTimeUS;
      _driveInfo.selfcorrectionUS = (3.50 * 2); //+ 50.0;
      _driveInfo.timePauseMS = (_driveInfo.expectedStepDurationMS * 1000) - _driveInfo.timePulsMS - _driveInfo.selfcorrectionUS; 
    };
      
  return _driveInfo;
  }
}

struct driveInfo Go(struct driveInfo _driveInfo) {

  // CHECK IF _driveInfo.timePulsMS > 5ms

  if (_driveInfo.timePulsMS < 0){
    while (1){
      Serial << "Wrong rotation settings! timePuls < 0ms: " << _driveInfo.timePulsMS  << "\n";
      blinkStart(200);
    }
  }

  unsigned int i;
  Serial << "GO: steps: " << _driveInfo.stepsTOgo << ", puls " << _driveInfo.timePulsMS << " us, pause " << _driveInfo.timePauseMS << " us, selfcorrection: " << _driveInfo.selfcorrectionUS << " us" << "\n";
  long int gt1 = millis();
  for ( i = 0; i < _driveInfo.stepsTOgo; i++ ){ 
    digitalWrite(_driveInfo.stepPin, HIGH);
    // PORTD = PORTD | B01000000; 
    //delay(_driveInfo.timePulsMS);
    delayMicroseconds(_driveInfo.timePulsMS);
    digitalWrite(_driveInfo.stepPin, LOW);
    //PORTD = PORTD & B01000000;
    delayMicroseconds((_driveInfo.timePauseMS));
  }
  long int gt2 = millis();
  double overtime = (gt2-gt1) - _driveInfo.expectedWorkTimeMS;
  if (overtime != 0){
     _driveInfo.selfcorrectionUS += (overtime/_driveInfo.stepsTOgo)*1000;
    _driveInfo.timePauseMS -= (overtime/_driveInfo.stepsTOgo)*1000;   
  }
  Serial << "GO: expected: " << _driveInfo.expectedWorkTimeMS << " ms, actual: " <<  _driveInfo.expectedWorkTimeMS + overtime  << " ms" << "\n";
  return _driveInfo;
}

void blinkStart(int t){
  unsigned int i;

   for ( i = 0; i < 5; i++ ){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(t);
    digitalWrite(LED_BUILTIN, LOW);
    delay(t);
   }
}

struct driveInfo SetDirection(struct driveInfo _driveInfo) {
  if (_driveInfo.startDir == true) {
    _driveInfo.currentDir = true;}
  else {
    _driveInfo.currentDir = false;};
  digitalWrite(_driveInfo.dirPin, _driveInfo.currentDir);
  return _driveInfo;
}

struct driveInfo ChangeDirection(struct driveInfo _driveInfo) {
  if (_driveInfo.currentDir == true) {
    _driveInfo.currentDir = false;}
  else {
    _driveInfo.currentDir = true;};
  digitalWrite(_driveInfo.dirPin, _driveInfo.currentDir);
  return _driveInfo;
}

void setup() {
  Serial.begin(9600);
  // Setting pins as OUTPUT
  pinMode(driveONEDirPin, OUTPUT);
  pinMode(driveONEStepPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
   // Setting all Pboard ports to LOW
  PORTD = B00000000;
  
  driveOne = GetDriveInfo(1);
  struct driveInfo driveONEInfo;
  driveOne = SetDirection(driveOne);
  Serial.println("Setup is done, starting the main programm");
}


void loop() {
  LoopCounter++;
  Serial << "Starting loop #" << LoopCounter << '\n';
  blinkStart(500);
  digitalWrite(LED_BUILTIN, HIGH);
  long int t1 = millis();
  driveOne = Go(driveOne);
  digitalWrite(LED_BUILTIN, LOW);
  driveOne = ChangeDirection(driveOne);
  long int t2 = millis();
  Serial.print("Loop took "); Serial.print(float(t2-t1)/1000); Serial<< " sec" << '\n';
  delay(99999999);
}
