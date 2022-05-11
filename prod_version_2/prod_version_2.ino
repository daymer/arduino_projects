#include "List.hpp"
#include "script_tasks.h"

template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

struct DriveActions {
    String a; //dirs
    String b; //steps
};

#include "setup.h"

void init_drive(int drive_num){
  struct DriveActions d_actions;
  String drive_1_actions = "d;0;0|s;0;100;10;|d;10;1|s;11;100;10;|";
  String drive_2_actions = "d;0;0|s;0;50;2;|d;5.1;1|s;25;50;2;|";

  if (drive_num==1){
    d_actions = make_action_lists(drive_1_actions, drive_num);
  }
  else if (drive_num==2){
    d_actions = make_action_lists(drive_2_actions, drive_num);
  }
  
  int step_point = 0;
  while (step_point < d_actions.a.length())  {
    String e = strSubs(d_actions.a, step_point, "|");
    step_point = step_point +  e.length() + 1;
    Serial << e  << '\n';};
  step_point = 0;
  while (step_point < d_actions.b.length())  {
    String e = strSubs(d_actions.b, step_point, "|");
    step_point = step_point +  e.length() + 1;
    Serial << e  << '\n';};
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
