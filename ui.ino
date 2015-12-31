#include "ui.h"

void pollRotaryEncoder() {
  int n = digitalRead(PIN_ENCODER0A);
  if ( (encoder0PinALast == LOW) && (n == HIGH) ) {
    if (digitalRead(PIN_ENCODER0B) == LOW) {
      tuneDown();
    } else {
      tuneUp();
    }
  } 
  encoder0PinALast = n;
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
    while( digitalRead(PIN_MULTIFUNCTION_BUTTON) == HIGH ){ }  // added for testing
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Multi_Function_Button++;
    if (Step_Multi_Function_Button > 2 ) { 
      Step_Multi_Function_Button = 0; 
    }
  }
  Step_Function();
}

void Step_Function() {
  switch ( Step_Multi_Function_Button ) {
    case 0:
      MF_G();
      Step_Select_Button = Selected_BW; // 
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 1:
      MF_Y();
      Step_Select_Button = Selected_Step; //
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 2: 
      MF_R();
      Step_Select_Button = Selected_Other; //
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //  
  }
}

void  pollSelectButton() {
  if (digitalRead(PIN_SELECT_BUTTON) == HIGH) {   
    while( digitalRead(PIN_SELECT_BUTTON) == HIGH ){ }  // added for testing
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Select_Button++;
    if (Step_Select_Button > 2 ) { 
      Step_Select_Button = 0; 
    }
  }
  Step_Select(); 
}

void Step_Select() {
  switch ( Step_Select_Button ) {
    case 0: //   PIN_SELECT_GREEN   could place the S_G() routine here!
      S_G();
      break;
    case 1: //   PIN_SELECT_YELLOW  could place the S_Y() routine here!
      S_Y();
      break; 
    case 2: //   PIN_SELECT_RED    could place the S_R() routine here!
      S_R();
      break;     
  }
}

void MF_G() {  //  Multi-function Green 
  digitalWrite(PIN_MULTIFUNCTION_GREEN, HIGH);    
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, LOW);  // 
  digitalWrite(PIN_MULTIFUNCTION_RED, LOW);  //
  for (int i=0; i <= 255; i++); // short delay   
}

void MF_Y() { //  Multi-function Yellow
  digitalWrite(PIN_MULTIFUNCTION_GREEN, LOW);    
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, HIGH);  // 
  digitalWrite(PIN_MULTIFUNCTION_RED, LOW);  //
  for (int i=0; i <= 255; i++); // short delay 
}

void MF_R() { //  Multi-function Red
  digitalWrite(PIN_MULTIFUNCTION_GREEN, LOW);
  digitalWrite(PIN_MULTIFUNCTION_YELLOW, LOW);  // 
  digitalWrite(PIN_MULTIFUNCTION_RED, HIGH);
  for (int i=0; i <= 255; i++); // short delay  
}

void S_G() { // Select Green 
  digitalWrite(PIN_SELECT_GREEN, HIGH); 
  digitalWrite(PIN_SELECT_YELLOW, LOW);  // 
  digitalWrite(PIN_SELECT_RED, LOW);  //
  if (Step_Multi_Function_Button == 0) {
    setBandwidth(BANDWIDTH_WIDE);
  } else if (Step_Multi_Function_Button == 1) {
    setStepSize(STEP_100HZ);
  } else if (Step_Multi_Function_Button == 2) {
      Other_1(); 
  }
  for (int i=0; i <= 255; i++); // short delay   
}

void S_Y() { // Select Yellow
  digitalWrite(PIN_SELECT_GREEN, LOW); 
  digitalWrite(PIN_SELECT_YELLOW, HIGH);  // 
  digitalWrite(PIN_SELECT_RED, LOW);  //
  if (Step_Multi_Function_Button == 0) {
    setBandwidth(BANDWIDTH_MEDIUM);
  } else if (Step_Multi_Function_Button == 1) {
    setStepSize(STEP_1000HZ); 
  } else if (Step_Multi_Function_Button == 2) {
      Other_2();
  }
  for (int i=0; i <= 255; i++); // short delay   
}

void S_R() { // Select Red
  digitalWrite(PIN_SELECT_GREEN, LOW);   //
  digitalWrite(PIN_SELECT_YELLOW, LOW);  // 
  digitalWrite(PIN_SELECT_RED, HIGH);    //
  if (Step_Multi_Function_Button == 0) {
    setBandwidth(BANDWIDTH_NARROW);
  } else if (Step_Multi_Function_Button == 1) {
    setStepSize(STEP_10000HZ); 
  } else if (Step_Multi_Function_Button == 2) {
      Other_3(); 
  }
  for (int i=0; i <= 255; i++); // short delay
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
