#include "List.hpp"
#include "script_tasks.h"

bool gDEBUG = false;

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

struct DriveActions d_actions_1;
struct DriveActions d_actions_2;

uint8_t BUFA; // stage on odd
uint8_t BUFB;

unsigned long TotalI;
unsigned long I=0;
int TotalWorkTimeSec = 60;
long int Tsec_start;

#include "setup.h"
#include "setter.h"

struct DriveActions init_drive(int drive_num){
  struct DriveActions d_actions;
  String drive_1_actions = "d;0;0|s;0;100;10;|d;10;1|s;11;100;10;|";
  String drive_2_actions = "d;0;0|s;0;50;2;|d;5.1;1|s;25;50;2;|";

  if (drive_num==1){
    d_actions = make_action_lists(drive_1_actions, drive_num);
  }
  else if (drive_num==2){
    d_actions = make_action_lists(drive_2_actions, drive_num);
  }

  if (gDEBUG){
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
  };
  return d_actions;
}

void setup() {
  Serial.begin(9600);
  Serial << "Setup is starting..." << '\n';
  
  TotalI = (TotalWorkTimeSec * 1000 * 1000) / 64;
  Serial << "Making actions, drive 1" << '\n';
  d_actions_1 = init_drive(1);
  Serial << "Making actions, drive 2" << '\n';
  d_actions_2 = init_drive(2);

  Serial << "Setting drive pins" << '\n';
  //DDRD = B00000000; // digital 0~7 set to input
  //DDRD = DDRD | B11111100; // digital 2~7 set to output

  DDRD &= ~bit(DDD0); PORTD |= bit(PORTD0); // set digital pin 0 as INPUT_PULLUP
  DDRD &= ~bit(DDD1); PORTD |= bit(PORTD1); // set digital pin 0 as INPUT_PULLUP

  DDRD |= bit(DDD2);                        // set digital pin 2 as OUTPUT
  DDRD |= bit(DDD3);                        // set digital pin 3 as OUTPUT
  DDRD |= bit(DDD4);                        // set digital pin 4 as OUTPUT
  DDRD |= bit(DDD5);                        // set digital pin 5 as OUTPUT

  BUFA = B00000000;
  BUFB = B11111100; 

  
  
  Serial << "Setup is complited, target I: " << TotalI << '\n';



  Tsec_start = millis();
}

unsigned long
  currentMillis,
  previousMillis;

int pause_mills = 1000;

void loop() {
  I++;
  // each loop should be exact 64 micro sec
  currentMillis  = millis();


    }
  }
