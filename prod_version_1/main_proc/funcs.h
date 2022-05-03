
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


void blinkStart(int t){
  unsigned int i;

   for ( i = 0; i < 5; i++ ){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(t);
    digitalWrite(LED_BUILTIN, LOW);
    delay(t);
   }
}

struct driveInfo WarmingUp(struct driveInfo _driveInfo) {
  // Move drive to oposite  the untill interruptPinLeft will rise
  // bool _direction = !_driveInfo.startDir;
  int steps_done_1 = 0;
  int steps_done_2 = 0;
  int interruptPin_1;
  struct driveInfo _drive;

  if (_driveInfo.startDir){
    interruptPin_1 = interruptPinRight;
  }
  else {
    interruptPin_1 = interruptPinLeft;
  };
  _drive = ChangeDirection(_driveInfo);

  while (!digitalRead(interruptPin_1)){
    digitalWrite(_driveInfo.stepPin, HIGH);
    delayMicroseconds(driveONEWarmingFixedPulsTimeUS);
    digitalWrite(_driveInfo.stepPin, LOW);
    delayMicroseconds((driveONEWarmingFixedPauseTimeUS));
    steps_done_1++;
  };

  _drive = ChangeDirection(_drive);
  while (digitalRead(interruptPin_1)){
    digitalWrite(_driveInfo.stepPin, HIGH);
    delayMicroseconds(driveONEWarmingFixedPulsTimeUS);
    digitalWrite(_driveInfo.stepPin, LOW);
    delayMicroseconds((driveONEWarmingFixedPauseTimeUS));
    steps_done_2++;
  };

  Serial << "Warmin if drive #" << _drive.num << " is done in " << steps_done_1 << " + " << steps_done_2 << " steps" << '\n';
  return _drive;
}

struct driveInfo Go(struct driveInfo _driveInfo) {

  if (_driveInfo.timePulsMS <= 0){
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