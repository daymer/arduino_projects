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

void init_drive(int drive_num){
  struct DriveActions d_actions;
  unsigned char drive_1_actions_num = 4;
    String drive_1_actions[] = {
      "d;0;0",
      "s;0;100;10;", // sec//distance in mm//speed mm/sec
      "d;10;1",
      "s;11;100;10;"
    };


unsigned char drive_2_actions_num = 4;
    String drive_2_actions[] = {
      "d;0;0",
      "s;0;50;2;",
      "d;5.1;1",
      "s;10;50;2;"
    };
  if (drive_num==1){
    d_actions = make_action_lists(drive_1_actions, drive_1_actions_num, 1);
    
  }
  else if (drive_num==2){
    d_actions = make_action_lists(drive_2_actions, drive_2_actions_num, 2);
  }
  for (int i = 0; i<2; i++) 
    { 
      Serial << d_actions.a[i].i << "," << d_actions.a[i].d  << '\n';
      Serial << d_actions.b[i].i << "," << d_actions.b[i].n << "," << d_actions.b[i].s  << '\n';
  };
}

void setup() {
  Serial.begin(9600);
  Serial << "Setup is starting..." << '\n';
  //int TotalWorkTimeSec = 60;
  //unsigned long TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
  Serial << "Making actions, drive 2" << '\n';
  init_drive(2);
  //Serial << "Making actions, drive 2" << '\n';
  //init_drive(2);
 
  //Serial << "Making actions, drive 2" << '\n';
  //struct DriveActions d_2_actions = make_action_lists(drive_2_actions, drive_2_actions_num, 2);
  
  Serial << "Setup is complited, SRAM: " << '\n';
}

void loop() {
  // put your main code here, to run repeatedly:

}
