
void drive_app_switch(String prog, int pin, int steps_to_make){
    if (currentMillis - previousMillis >= pause_mills*StepLengthMicSec) {
          // time is up
       //Serial << "I: " << currentMillis - previousOnBoardLedMillis << '\n';;
          // and save the time when we made the change
       bitWrite(BUFA, pin, 1);
       steps_to_make++
       previousOnBoardLedMillis += pause_mills*StepLengthMicSec;
          // NOTE: The previous line could alternatively be
          //              previousOnBoardLedMillis = currentMillis
          //        which is the style used in the BlinkWithoutDelay example sketch
          //        Adding on the interval is a better way to ensure that succesive periods are identical
        else         
  }
}
void drive_app_step(String prog){
  
}
