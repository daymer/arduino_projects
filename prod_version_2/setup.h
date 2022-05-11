#include "drive_setup.h"
bool DEBUG = true;

struct DriveActions make_action_lists(String drive_actions[], char arraySize, char drive_num){
  struct DriveActions _result;
  int steps = -1;
  int dirs = -1;
  
  for (char a=0; a <= arraySize-1; a++) {
    String e = drive_actions[a];
    char point = 2;
    if (DEBUG){
      Serial << "RAW Task: " << e << '\n';
    };
    if (e.substring(0,1) == "d"){
        dirs++;
        if (DEBUG){
              Serial << "RAW DIR Task #" << dirs << '\n';
            };
        String t = strSubs(e, point);
        long  i = toI(t.toFloat()); //// Start second -> Start I calc
        if (DEBUG){
              Serial << "RAW DIR Task: $i " << i << ", String: " << String(i) << '\n';
            };
        point = point + t.length();
        bool  d = e.substring(point+1,point+2).toInt(); //// Dir
         if (DEBUG){
              Serial << "RAW DIR Task: $d " << d << ", String: " << String(d) << '\n';
            };
        _result.a.add(String(i)+";"+String(d));
        if (DEBUG){
              Serial << "DIR Task: " << String(i)+";"+String(d) << '\n';
              Serial << "translated: on " << t << " second (I=" << i <<") switch to " << d << '\n';
            };
      }
    else {
        steps++;
        if (DEBUG){
              Serial << "RAW STEP Task #" << steps << '\n';
            };
        String t = strSubs(e, point);
        point = point + t.length();
        long i = toI(t.toFloat()); //// Start second -> Start I calc
        if (DEBUG){
              Serial << "RAW STEP Task: $i " << i << ", String: " << String(i) << '\n';
            };
        String n = strSubs(e, point+1);
        point = point + n.length();
        String s = strSubs(e, point+2);
        float spd = s.toFloat(); //// Speed mm\s
        struct N _n = toN(n.toInt(), spd, drive_num); //// MM to go  -> N to go (aka peeks), transitional state! will be a total N
         if (DEBUG){
              Serial << "RAW STEP Task: $_n.t_n " << _n.t_n << ", String: " << String(_n.t_n) << '\n';
              Serial << "RAW STEP Task: $_n.sleep_n " << _n.sleep_n << ", String: " << String(_n.sleep_n) << '\n';
            };
        long sn = _n.t_n;
        int ss = _n.sleep_n;
         if (DEBUG){
              Serial << "RAW STEP Task: $sn " << sn << ", String: " << String(sn) << '\n';
              Serial << "RAW STEP Task: $ss " << ss << ", String: " << String(ss) << '\n';
            };
        
        _result.b.add(String(i)+";"+String(sn)+";"+String(ss));
        if (DEBUG){
              Serial << "STEP Task: " << String(i)+";"+String(sn)+";"+String(ss) << '\n';
              Serial << "translated: starting on " << t << " second (I = " << i <<") do " << n <<  " mm in " <<  spd << " mm/sec" <<'\n';
              Serial << "           totally: 64 mics * " << sn << " steps, each " << "frequency: 1:" << ss <<'\n';
            };
        
      }
  };
  return _result;
 }
