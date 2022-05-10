template <typename T>
Print& operator<<(Print& printer, T value)
{
    printer.print(value);
    return printer;
}

#include "setup.h"

void setup() {
  Serial.begin(9600);
  Serial << "Setup is starting..." << '\n';
  make_action_lists(drive_1_actions, drive_1_actions_num);
  make_action_lists(drive_2_actions, drive_2_actions_num);
  Serial << "Setup is complited" << '\n';
}

void loop() {
  // put your main code here, to run repeatedly:

}
