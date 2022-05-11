#include "List.hpp"
#include "script_tasks.h"

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

struct DriveActions {
    List<String> a; //dirs
    List<String> b; //steps
};

#include "setup.h"

void init_drive(int drive_num){
  struct DriveActions d_actions;
  
    List<String> drive_1_actions;
    drive_1_actions.add("d;0;0");
    drive_1_actions.add("s;0;100;10;");
    drive_1_actions.add("d;10;1");
    drive_1_actions.add("s;11;100;10;");
  
    List<String> drive_2_actions; 
    drive_2_actions.add("d;0;0");
    drive_2_actions.add("s;0;50;2;");
    drive_2_actions.add("d;5.1;1");
    drive_2_actions.add("s;25;50;2;");

  if (drive_num==1){
    d_actions = make_action_lists(drive_1_actions, 1);
  }
  else if (drive_num==2){
    d_actions = make_action_lists(drive_2_actions, 2);
  }
  for (int i = 0; i < d_actions.a.getSize(); i++) 
    { 
      Serial << d_actions.a[i]  << '\n';
  };
  for (int i = 0; i < d_actions.b.getSize(); i++) 
    { 
      Serial << d_actions.b[i]  << '\n';
  };
}

void setup() {
  Serial.begin(9600);
  Serial << "Setup is starting..." << '\n';
  //int TotalWorkTimeSec = 60;
  //unsigned long TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
  Serial << "Making actions, drive 1" << '\n';
  init_drive(1);
  Serial << "Making actions, drive 2" << '\n';
  init_drive(2);
 
  //Serial << "Making actions, drive 2" << '\n';
  //struct DriveActions d_2_actions = make_action_lists(drive_2_actions, drive_2_actions_num, 2);
  
  Serial << "Setup is complited, SRAM: " << '\n';
}

void loop() {
  // put your main code here, to run repeatedly:

}
