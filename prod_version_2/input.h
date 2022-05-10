int driveONEstepsPerRota = 200; // steps per 1 rotation
double driveONEmmPerRota = 3.5; // mm per 1 rotation

int driveTWOstepsPerRota = 200; // steps per 1 rotation
double driveTWOmmPerRota = 3.5; // mm per 1 rotation // REQ CALIBRATION


// -----INPUT-----
// -----1-----
double driveONEdistanceMM = 10; // TO GO in mm; ? max // REQ CALIBRATION
double driveONESpeed = 10.0; // Speed in mm/sec; 17.0 max
bool driveONEStartDir = true; // true = HIGH (left, in), false = LOW (right, out)

// -----2-----
double driveTWOdistanceMM = 10; // TO GO in mm; ? max
double driveTWOSpeed = 10.0; // Speed in mm/sec; 17.0 max
bool driveTWOStartDir = true; // true = HIGH (left, in), false = LOW (right, out) // REQ CALIBRATION

// ---------------

// -----Modes-----
#define PulsCalcMode 2

// PulsCalcMode 1: calc puls\pause by percent (currently unused)
// -----1-----
double driveONETimePulsPercent = 0.4; //how long to send signal, float // REQ CALIBRATION
double driveONETimePausePercent = 1 - driveONETimePulsPercent; //pause before and after signal, float // REQ CALIBRATION
// -----2-----
double driveTWOTimePulsPercent = 0.4; //how long to send signal, float // REQ CALIBRATION
double driveTWOTimePausePercent = 1 - driveTWOTimePulsPercent; //pause before and after signal, float // REQ CALIBRATION

// PulsCalcMode 2: calc puls\pause time by fixed length
// -----1-----
int driveONEFixedPulsTimeUS = 64; //us
int driveONEWarmingFixedPulsTimeUS = 64; //us
int driveONEWarmingFixedPauseTimeUS = 929; //us
// -----2-----
int driveTWOFixedPulsTimeUS = 64; //us
int driveTWOWarmingFixedPulsTimeUS = 64; //us
int driveTWOWarmingFixedPauseTimeUS = 929; //us
// ---------------
