struct driveInfo GetDriveInfo(int driveNum) {
   // Defining driveDirPin and driveCurrentDir
  struct driveInfo _driveInfo;
  if (driveNum == 1){
    _driveInfo.num = 1;
    _driveInfo.dirPin = driveONEDirPin;
    _driveInfo.stepPin = driveONEStepPin;
    
    //input
    _driveInfo.startDir = driveONEStartDir;

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
      return _driveInfo;}

  else if (driveNum == 2){
    _driveInfo.num = 2;
    _driveInfo.dirPin = driveTWODirPin;
    _driveInfo.stepPin = driveTWOStepPin;

    //input
    _driveInfo.startDir = driveTWOStartDir;

    _driveInfo.stepsPerMM = 1.0 / (driveTWOmmPerRota / driveTWOstepsPerRota); // REQ CALIBRATION 45.71428! #TODO: do smth with float
    _driveInfo.stepsTOgo = driveTWOdistanceMM * _driveInfo.stepsPerMM;
    _driveInfo.expectedWorkTimeMS = (driveTWOdistanceMM / driveTWOSpeed) * 1000; // MICRO SECONDS of work of driveOne
    _driveInfo.expectedStepDurationMS = _driveInfo.expectedWorkTimeMS / _driveInfo.stepsTOgo;

    if (PulsCalcMode == 1){
      _driveInfo.timePulsMS = _driveInfo.expectedStepDurationMS * driveTWOTimePulsPercent;
      _driveInfo.selfcorrectionUS = (3.50 * 2) + 50.0;
      _driveInfo.timePauseMS = (_driveInfo.expectedStepDurationMS * driveTWOTimePausePercent * 1000) - _driveInfo.selfcorrectionUS;
      }
    else if (PulsCalcMode == 2){
      _driveInfo.timePulsMS = driveTWOFixedPulsTimeUS;
      _driveInfo.selfcorrectionUS = (3.50 * 2); //+ 50.0;
      _driveInfo.timePauseMS = (_driveInfo.expectedStepDurationMS * 1000) - _driveInfo.timePulsMS - _driveInfo.selfcorrectionUS;
    };
      return _driveInfo;
  }
}
