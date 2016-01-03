#include "ui.h"

void pollRotaryEncoder() {
  static int encoder0PinALast = LOW;
  static int encoder0PinBLast = LOW;
  
  int n = digitalRead(PIN_ENCODER0A);
  int m = digitalRead(PIN_ENCODER0B);
  
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (m == LOW) {
      tuneDown();    //encoder0Pos--;
    } else {
      tuneUp();       //encoder0Pos++;
    }
  } else if ((encoder0PinALast == HIGH) && (n == LOW)) {
    // now we get 36 steps/rev instead of 10
    if (m == HIGH) {
      tuneDown();
    } else {
      tuneUp();
    }
  } else if ((encoder0PinBLast == LOW) && (m == HIGH)) {
    if (n == LOW) {
      tuneUp();
    } else {
      tuneDown();
    }
  } else if ((encoder0PinBLast == HIGH) && (m == LOW)) {
    if (n == HIGH) {
      tuneUp();
    } else {
      tuneDown();
    }
  }
  encoder0PinALast = n;
  encoder0PinBLast = m;
/*
  int n = digitalRead(PIN_ENCODER0A);
  if ( (encoder0PinALast == LOW) && (n == HIGH) ) {
    if (digitalRead(PIN_ENCODER0B) == LOW) {
      tuneDown();
    } else {
      tuneUp();
    }
  } 
  encoder0PinALast = n;
*/
}

void pollRIT() {
  int oldRitValue;
  oldRitValue = RitReadValue;
  RitReadValue = (analogRead(PIN_RIT) + (7 * RitReadValue))/8;//Lowpass filter
  if (RitReadValue != oldRitValue) {
    if(RitReadValue < 500) {
      RitFrequencyOffset = RitReadValue-500;
    } else if(RitReadValue < 523) {
      RitFrequencyOffset = 0;//Deadband in middle of pot
    } else {
      RitFrequencyOffset = RitReadValue - 523;
    }
    setFrequency(currentFrequency);
  }
}

void pollMultifunctionButton() { // The right most pushbutton for BW, Step, Other
  if (digitalRead(PIN_MULTIFUNCTION_BUTTON) == HIGH) {   
    while( digitalRead(PIN_MULTIFUNCTION_BUTTON) == HIGH ){ } // Wait for the button to be released
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Multi_Function_Button++;
    if (Step_Multi_Function_Button > 2 ) { 
      Step_Multi_Function_Button = 0; 
    }
    setMultifunction(Step_Multi_Function_Button);
  }
}

void setMultifunction(int newFunction) {
  switch ( newFunction ) {
    case MULTIFUNCTION_1:
      Step_Select_Button = Selected_BW; // 
      break;   //
    case MULTIFUNCTION_2:
      Step_Select_Button = Selected_Step; //
      break;   //
    case MULTIFUNCTION_3: 
      Step_Select_Button = Selected_Other; //
      break;   //  
  }
  setMultifunctionLED(newFunction);
  setFunctionLED(Step_Select_Button); //Display the current value for this function
}

void setMultifunctionLED(int func) {
  digitalWrite(PIN_MULTIFUNCTION_GREEN, (func == MULTIFUNCTION_1) );
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, (func == MULTIFUNCTION_2) );
  digitalWrite(PIN_MULTIFUNCTION_RED, (func == MULTIFUNCTION_3) );
}

void  pollSelectButton() {
  if (digitalRead(PIN_SELECT_BUTTON) == HIGH) {   
    while( digitalRead(PIN_SELECT_BUTTON) == HIGH ){ } //Wait for the button to be released
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Select_Button++;
    if (Step_Select_Button > 2 ) { 
      Step_Select_Button = 0; 
    }
    setFunction(Step_Select_Button);
  }
}

void setFunction(int newFunction) {
  switch ( newFunction ) {
    case FUNCTION_1:
      if (Step_Multi_Function_Button == 0) {
        setBandwidth(BANDWIDTH_WIDE);
      } else if (Step_Multi_Function_Button == 1) {
        setStepSize(STEP_100HZ);
      } else if (Step_Multi_Function_Button == 2) {
        Other_1(); 
      }
      break;
    case FUNCTION_2:
      if (Step_Multi_Function_Button == 0) {
        setBandwidth(BANDWIDTH_MEDIUM);
      } else if (Step_Multi_Function_Button == 1) {
        setStepSize(STEP_1000HZ); 
      } else if (Step_Multi_Function_Button == 2) {
        Other_2();
      }
      break; 
    case FUNCTION_3:
      if (Step_Multi_Function_Button == 0) {
        setBandwidth(BANDWIDTH_NARROW);
      } else if (Step_Multi_Function_Button == 1) {
        setStepSize(STEP_10000HZ); 
      } else if (Step_Multi_Function_Button == 2) {
        Other_3(); 
      }
      break;     
  }
  setFunctionLED(newFunction);
  serialSend(SERIAL_BANDWIDTH, Selected_BW);
  serialSend(SERIAL_STEPSIZE, Selected_Step);
  serialSend(SERIAL_USER, Selected_Other);
}

void setFunctionLED(int func) {
  digitalWrite(PIN_SELECT_GREEN, (func == FUNCTION_1) ); 
  digitalWrite(PIN_SELECT_YELLOW, (func == FUNCTION_2) );  // 
  digitalWrite(PIN_SELECT_RED, (func == FUNCTION_3) );  //
}

void Other_1() {    //  User Defined Control Software 
  Selected_Other = USER_1; 
}

void Other_2() {    //  User Defined Control Software
  Selected_Other = USER_2; 
}

void Other_3() {     //  User Defined Control Software
  Selected_Other = USER_3; 
}
