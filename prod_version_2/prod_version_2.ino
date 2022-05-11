//#include "Arduino.h"
#include "script_tasks.h"

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

struct DriveActions {
    struct DirTask a[1];
    struct StepTask b[1];
};

#include "setup.h"

void setup() {
  Serial.begin(9600);
  Serial << "Setup is starting..." << '\n';
  //int TotalWorkTimeSec = 60;
  //unsigned long TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
    
  
  struct DriveActions d_1_actions = make_action_lists(drive_1_actions, drive_1_actions_num, 1);
  Serial << "Drive 1 actions object size: " << sizeof(d_1_actions) << '\n';
  
  
  //Serial << "Making actions, drive 2" << '\n';
  //struct DriveActions d_2_actions = make_action_lists(drive_2_actions, drive_2_actions_num, 2);
  
  Serial << "Setup is complited, SRAM: " << '\n';
}

void loop() {
  // put your main code here, to run repeatedly:

}
