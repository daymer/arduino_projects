struct driveInfo {
  int num;
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
