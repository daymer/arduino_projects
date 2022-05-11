// put your setup script here
#include "drive_setup.h"

//int TotalWorkTimeMin = 1;
//int NumOfDrivesToUse = 2;
unsigned char StepLengthMicSec = 64;



//int total_actions_num = drive_1_actions_num + drive_2_actions_num;


struct N {
    int sleep_n;
    long t_n;
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

float toI(float sec){

      if (sec == 0){
          return 1.0;
        }
      else {
          //Serial << "DEBUG: #I: " << (sec * 1000000) / StepLengthMicSec << "\n";
          return (sec * 1000000) / StepLengthMicSec;
        };
  }



struct N toN(int mm, float spd, char d_num){
    unsigned char sPr;
    float mmPr;
    
    if (d_num == 1){
       mmPr = drive_1_mmPr;
       sPr = drive_1_sPr;
      }
    else if (d_num == 2){
       mmPr = drive_2_mmPr;
       sPr = drive_2_sPr;
      }
    else {
        while (1){
          Serial << "Drive #" << d_num << "REQs CALIBRATION!" << "\n";
        }
      };
    
    float stepsPmm = 1.0 / (mmPr / sPr);
    //Serial << "DEBUG: stepsPmm " << stepsPmm << "\n";
    long peeks = mm * stepsPmm; 
    long t_peeks_mics = peeks * StepLengthMicSec;
    long exp_wtime_mics = (mm / spd) * 1000 * 1000;
    long exp_total_pause_mics = exp_wtime_mics - t_peeks_mics;
    
    //Serial << "DEBUG: peeks " << peeks << "\n"; 
    //Serial << "DEBUG: t_peeks_mics " << t_peeks_mics << "\n"; 
    //Serial << "DEBUG: exp_wtime_mics " << exp_wtime_mics << "\n";
    //Serial << "DEBUG: exp_total_pause_mics " << exp_total_pause_mics << "\n";    

    long exp_step_duration_mics = exp_wtime_mics / peeks;
     //Serial << "DEBUG: exp_step_duration_mics " << exp_step_duration_mics << "\n";
     
    struct N _n;
    _n.sleep_n = (int) (exp_step_duration_mics - StepLengthMicSec) / StepLengthMicSec ;
    // expectations
    long t_n_exp =  exp_wtime_mics / StepLengthMicSec;
    // reality
    _n.t_n =  (long) (_n.sleep_n + 1) * peeks;
    //Serial << "DEBUG: t_n " << _n.t_n << "; t_n_exp: " << t_n_exp << ", _n.sleep_n: " << _n.sleep_n << "\n";
    //Serial << "DEBUG: A DIFF = " << (t_n_exp - _n.t_n) * StepLengthMicSec / 1000  << " millisec!" << "\n";
    //Serial << "DEBUG: A DIFF = " << (t_n_exp - _n.t_n)  << " Ns!" << "\n";
    // TODO: this will be a question for speed-up \ slow down 
    return _n;
  }

struct DriveActions make_action_lists(String drive_actions[], char arraySize, char drive_num){
  struct DriveActions _result;
  char steps = -1;
  char dirs = -1;
  for (char a=0; a <= arraySize-1; a++) { // for each element in the array
    String e = drive_actions[a];
    char point = 2;
    if (e.substring(0,1) == "d"){
        dirs = dirs++;
        struct DirTask _task;
        String t = strSubs(e, point);
            _task.i = toI(t.toFloat()); //// Start second -> Start I calc
        point = point + t.length();
            _task.d = e.substring(point+1,point+2).toInt(); //// Dir
        _result.a[dirs] = _task;
        //Serial << "Dir task: on " << t << " second (I = " << _task.i <<") switch to " << _task.d << '\n';
      }
    else {
        steps = steps++;
        struct StepTask _task;
        String t = strSubs(e, point);
        point = point + t.length();
        _task.i = toI(t.toFloat()); //// Start second -> Start I calc
        String n = strSubs(e, point+1);
        point = point + n.length();
        String s = strSubs(e, point+2);
        float spd = s.toFloat(); //// Speed mm\s
        struct N _n = toN(n.toInt(), spd, drive_num); //// MM to go  -> N to go (aka peeks), transitional state! will be a total N
        _task.n = _n.t_n;
        _task.s = _n.sleep_n;
        _result.b[steps] = _task;
        //Serial << "Step task: starting on " << t << " second (I = " << _task.i <<") do " << n <<  " mm in " <<  spd << " mm/sec" <<'\n';
        //Serial << "           totally: 64 mics * " << _task.n << " steps, each " << "frequency: 1:" << _task.s <<'\n';
      }
  };
  return _result;
 }
