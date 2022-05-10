// put your setup script here
#include "script_tasks.h"
#include "drive_setup.h"

//int TotalWorkTimeMin = 1;
//int NumOfDrivesToUse = 2;
unsigned char StepLengthMicSec = 64;

int drive_1_actions_num = 4;
String drive_1_actions[] = {
  "d;0;0",
  "s;0;10;1;", // sec//distance in mm//speed mm/sec
  "d;10;1",
  "s;11;10;1;"
};


int drive_2_actions_num = 4;
String drive_2_actions[] = {
  "d;0;0",
  "s;0;10;2;",
  "d;5.1;1",
  "s;10;10;2;"
};

//int total_actions_num = drive_1_actions_num + drive_2_actions_num;

struct DriveActions {
    struct DirTask a[1];
    struct StepTask b[1];
};

String strSubs(String src_str, int point){
  String t = "";
  String c = src_str.substring(point, point++);
  while (c != ";"){
      t += c;
      c = src_str.substring(point,point++);
    };
  return t;
  }

unsigned long toI(float sec){
   unsigned long i = 0;
      if (sec == 0){
          i = 1;
        }
      else {
          i = (sec * 1000 * 1000) / StepLengthMicSec;
        };
     return i;
  }

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
        String t = strSubs(e, point);
        _task.i = toI(t.toFloat()); //// converting seconds to I here
        point = point + t.length();
        _task.d = e.substring(point+1,point+2).toInt();
        _result.a[dirs] = _task;
        Serial << "Dir task: on " << t << " second (I = " << _task.i <<") switch to " << _task.d << '\n';
      }
    else {
        steps = steps++;
        struct StepTask _task;
        String t = strSubs(e, point);
        point = point + t.length();
           _task.i = toI(t.toFloat()); //// converting seconds to I here
        String n = strSubs(e, point+1);
        point = point + n.length();
            _task.n = n.toInt();
        String m = strSubs(e, point+2);
            _task.m = m.toInt();
        _result.b[steps] = _task;
        Serial << "Step task: from " << t << " second (I = " << _task.i <<") run " << n <<  " mm on " <<  m << " mm/sec" <<'\n';
      }
  };
 }





// Followers
//int TotalWorkTimeSec = TotalWorkTimeMin * 60;
//unsigned long TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
