unsigned char drive_1_sPr = 200; // steps per 1 rotation
float drive_1_mmPr = 3.5; // mm per 1 rotation

unsigned char drive_2_sPr = 200; // REQ CAL
float drive_2_mmPr = 3.5; // REQ CAL

unsigned char StepLengthMicSec = 64;

String strSubs(String src_str, int point, String del){
  String t = "";
  String c = src_str.substring(point, point++);
  while (c != del){
      t += c;
      c = src_str.substring(point,point++);
    };
  return t;
  }


struct N {
    int sleep_n;
    long t_n;
};


long toI(float sec){

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
