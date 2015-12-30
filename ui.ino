#include "ui.h"

bool getDitKey() {
  return (digitalRead(PIN_KEY_DIT) == LOW);
}

bool getDahKey() {
  return (digitalRead(PIN_KEY_DAH) == LOW);
}

void pollRotaryEncoder() {
  n = digitalRead(PIN_ENCODER0A);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(PIN_ENCODER0B) == LOW) {
      setFrequency(bandLimit(currentFrequency - frequency_step));
    } else {
      setFrequency(bandLimit(currentFrequency + frequency_step));
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
  Step_Multi_Function_Button = digitalRead(PIN_MULTIFUNCTION_BUTTON);
  if (Step_Multi_Function_Button == HIGH) {   
    while( digitalRead(PIN_MULTIFUNCTION_BUTTON) == HIGH ){ }  // added for testing
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Multi_Function_Button1 = Step_Multi_Function_Button1++;
    if (Step_Multi_Function_Button1 > 2 ) { 
      Step_Multi_Function_Button1 = 0; 
    }
  }
  Step_Function();
}

void Step_Function() {
  switch ( Step_Multi_Function_Button1 ) {
    case 0:
      MF_G();
      Step_Select_Button1 = Selected_BW; // 
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 1:
      MF_Y();
      Step_Select_Button1 = Selected_Step; //
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 2: 
      MF_R();
      Step_Select_Button1 = Selected_Other; //
      Step_Select(); //
      pollSelectButton();
      for (int i=0; i <= 255; i++); // short delay
      break;   //  
  }
}

void  pollSelectButton() {
  Step_Select_Button = digitalRead(PIN_SELECT_BUTTON);
  if (Step_Select_Button == HIGH) {   
    while( digitalRead(PIN_SELECT_BUTTON) == HIGH ){ }  // added for testing
    for (int i=0; i <= 150e3; i++); // short delay
    Step_Select_Button1 = Step_Select_Button1++;
    if (Step_Select_Button1 > 2 ) { 
      Step_Select_Button1 = 0; 
    }
  }
  Step_Select(); 
}

void Step_Select() {
  switch ( Step_Select_Button1 ) {
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
  if (Step_Multi_Function_Button1 == 0) {
      Band_Width_W(); 
  } else if (Step_Multi_Function_Button1 == 1) {
      Step_Size_100(); 
  } else if (Step_Multi_Function_Button1 == 2) {
      Other_1(); 
  }
  for (int i=0; i <= 255; i++); // short delay   
}

void S_Y() { // Select Yellow
  digitalWrite(PIN_SELECT_GREEN, LOW); 
  digitalWrite(PIN_SELECT_YELLOW, HIGH);  // 
  digitalWrite(PIN_SELECT_RED, LOW);  //
  if (Step_Multi_Function_Button1 == 0) {
      Band_Width_M();
  } else if (Step_Multi_Function_Button1 == 1) {
      Step_Size_1k(); 
  } else if (Step_Multi_Function_Button1 == 2) {
      Other_2();
  }
  for (int i=0; i <= 255; i++); // short delay   
}

void S_R() { // Select Red
  digitalWrite(PIN_SELECT_GREEN, LOW);   //
  digitalWrite(PIN_SELECT_YELLOW, LOW);  // 
  digitalWrite(PIN_SELECT_RED, HIGH);    //
  if (Step_Multi_Function_Button1 == 0) {
      Band_Width_N();
  } else if (Step_Multi_Function_Button1 == 1) {
      Step_Size_10k(); 
  } else if (Step_Multi_Function_Button1 == 2) {
      Other_3(); 
  }
  for (int i=0; i <= 255; i++); // short delay
}

void Band_Width_W() {
  digitalWrite( PIN_MEDIUM_A8, LOW);   // Hardware control of I.F. filter shape
  digitalWrite( PIN_NARROW_A9, LOW);   // Hardware control of I.F. filter shape
  Selected_BW = BANDWIDTH_WIDE;
}

void Band_Width_M() {
  digitalWrite( PIN_MEDIUM_A8, HIGH);  // Hardware control of I.F. filter shape
  digitalWrite( PIN_NARROW_A9, LOW);   // Hardware control of I.F. filter shape
  Selected_BW = BANDWIDTH_MEDIUM;  
}

void Band_Width_N() {
  digitalWrite( PIN_MEDIUM_A8, LOW);   // Hardware control of I.F. filter shape
  digitalWrite( PIN_NARROW_A9, HIGH);  // Hardware control of I.F. filter shape
  Selected_BW = BANDWIDTH_NARROW; 
}

void Step_Size_100() {    // Encoder Step Size 
  frequency_step = 100;   //  Can change this whatever step size one wants
  Selected_Step = STEP_100HZ; 
}

void Step_Size_1k() {     // Encoder Step Size 
  frequency_step = 1e3;   //  Can change this whatever step size one wants
  Selected_Step = STEP_1000HZ; 
}

void Step_Size_10k() {    // Encoder Step Size 
  frequency_step = 10e3;    //  Can change this whatever step size one wants
  Selected_Step = STEP_10000HZ; 
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
