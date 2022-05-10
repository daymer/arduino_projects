// put your setup script here
#include "script_dir_task.h"
#include "script_step_task.h"
#include "Arduino.h"

int TotalWorkTimeMin = 1;
int NumOfDrivesToUse = 2;
int StepLengthMicSec = 64;

int drive_1_actions_num = 4;
String drive_1_actions[] = {
  "d;0;0",
  "s;0;10;1",
  "d;10;1",
  "s;11;10;1"
};

int drive_2_actions_num = 4;
String drive_2_actions[] = {
  "d;0;0",
  "s;0;10;2",
  "d;5.1;1",
  "s;10;10;2"
};

int total_actions_num = drive_1_actions_num + drive_2_actions_num;

struct DriveActions {
    struct DirTask a[1];
    struct StepTask b[1];
};


struct DriveActions make_action_lists(String drive_actions[], int arraySize){
  struct DriveActions _result;
  int steps = -1;
  int dirs = -1;
  for (int a=0; a <= arraySize-1; a++) { // for each element in the array
    String e = drive_actions[a];
    int point = 2;
    if (e.substring(0,1) == "d"){
        dirs = dirs++;
        struct DirTask _task;
        String t = "";
        String cur_char = e.substring(point, point+1);
        point = point + 1;
        while (cur_char != ";"){
          t += cur_char;
          cur_char = e.substring(point,point+1);
          point = point+1;
        };
        //// convert seconds to I here
        float seconds =  t.toFloat();
        unsigned long _i = 0;
        if (seconds == 0){
          _i = 1;
        }
        else {
          _i = (seconds * 1000 * 1000) / 64;
          };
        _task.i = _i;
        _task.d = e.substring(point++,point++).toInt();
        _result.a[dirs] = _task;
        Serial << "Dir task: on " << seconds << " second (I = " << _task.i <<") switch to " << _task.d << '\n';
      }
    else {
        steps = steps++;
        struct StepTask _task;

        
        _task.i = e.substring(2,3).toInt();
        _task.n = e.substring(4,5).toInt();
        _task.n_p = e.substring(6,7).toInt();
        _result.b[steps] = _task;
        Serial << "step: " << e << '\n';
      }
  };
 }


String strSubs(String src_str, int point){
  String t = "";
  String c = e.substring(point, point++);
  while (c != ";"){
      t += c;
      c = e.substring(point,point++);
    };
  return t;
  }


// Followers
int TotalWorkTimeSec = TotalWorkTimeMin * 60;
unsigned long TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
