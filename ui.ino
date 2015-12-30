#include "ui.h"

void Encoder() {
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      Frequency_down();    //encoder0Pos--;
    } else {
      Frequency_up();       //encoder0Pos++;
    }
  } 
  encoder0PinALast = n;
}

void Step_Flash() {
  stop_led_on();
  for (int i=0; i <= 25e3; i++); // short delay 
  stop_led_off();   
}

void stop_led_on() {
  digitalWrite(Band_End_Flash_led, HIGH);
}


void stop_led_off() {
  digitalWrite(Band_End_Flash_led, LOW);
}

void Multi_Function() { // The right most pushbutton for BW, Step, Other
  Step_Multi_Function_Button = digitalRead(Multi_Function_Button);
  if (Step_Multi_Function_Button == HIGH) {   
    while( digitalRead(Multi_Function_Button) == HIGH ){ }  // added for testing
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
      Selection();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 1:
      MF_Y();
      Step_Select_Button1 = Selected_Step; //
      Step_Select(); //
      Selection();
      for (int i=0; i <= 255; i++); // short delay
      break;   //
    case 2: 
      MF_R();
      Step_Select_Button1 = Selected_Other; //
      Step_Select(); //
      Selection();
      for (int i=0; i <= 255; i++); // short delay
      break;   //  
  }
}

void  Selection() {
  Step_Select_Button = digitalRead(Select_Button);
  if (Step_Select_Button == HIGH) {   
    while( digitalRead(Select_Button) == HIGH ){ }  // added for testing
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
    case 0: //   Select_Green   could place the S_G() routine here!
      S_G();
      break;
    case 1: //   Select_Yellow  could place the S_Y() routine here!
      S_Y();
      break; 
    case 2: //   Select_Red    could place the S_R() routine here!
      S_R();
      break;     
  }
}

void MF_G() {  //  Multi-function Green 
  digitalWrite(Multi_function_Green, HIGH);    
  digitalWrite(Multi_function_Yellow, LOW);  // 
  digitalWrite(Multi_function_Red, LOW);  //
  for (int i=0; i <= 255; i++); // short delay   
}

void MF_Y() { //  Multi-function Yellow
  digitalWrite(Multi_function_Green, LOW);    
  digitalWrite(Multi_function_Yellow, HIGH);  // 
  digitalWrite(Multi_function_Red, LOW);  //
  for (int i=0; i <= 255; i++); // short delay 
}

void MF_R() { //  Multi-function Red
  digitalWrite(Multi_function_Green, LOW);
  digitalWrite(Multi_function_Yellow, LOW);  // 
  digitalWrite(Multi_function_Red, HIGH);
  for (int i=0; i <= 255; i++); // short delay  
}

void S_G() { // Select Green 
  digitalWrite(Select_Green, HIGH); 
  digitalWrite(Select_Yellow, LOW);  // 
  digitalWrite(Select_Red, LOW);  //
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
  digitalWrite(Select_Green, LOW); 
  digitalWrite(Select_Yellow, HIGH);  // 
  digitalWrite(Select_Red, LOW);  //
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
  digitalWrite(Select_Green, LOW);   //
  digitalWrite(Select_Yellow, LOW);  // 
  digitalWrite(Select_Red, HIGH);    //
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
  digitalWrite( Medium_A8, LOW);   // Hardware control of I.F. filter shape
  digitalWrite( Narrow_A9, LOW);   // Hardware control of I.F. filter shape
  Selected_BW = Wide_BW;
}

void Band_Width_M() {
  digitalWrite( Medium_A8, HIGH);  // Hardware control of I.F. filter shape
  digitalWrite( Narrow_A9, LOW);   // Hardware control of I.F. filter shape
  Selected_BW = Medium_BW;  
}

void Band_Width_N() {
  digitalWrite( Medium_A8, LOW);   // Hardware control of I.F. filter shape
  digitalWrite( Narrow_A9, HIGH);  // Hardware control of I.F. filter shape
  Selected_BW = Narrow_BW; 
}

void Step_Size_100() {    // Encoder Step Size 
  frequency_step = 100;   //  Can change this whatever step size one wants
  Selected_Step = Step_100_Hz; 
}

void Step_Size_1k() {     // Encoder Step Size 
  frequency_step = 1e3;   //  Can change this whatever step size one wants
  Selected_Step = Step_1000_hz; 
}

void Step_Size_10k() {    // Encoder Step Size 
  frequency_step = 10e3;    //  Can change this whatever step size one wants
  Selected_Step = Step_10000_hz; 
}

void Other_1() {    //  User Defined Control Software 
  Selected_Other = Other_1_user; 
}

void Other_2() {    //  User Defined Control Software
  Selected_Other = Other_2_user; 
}

void Other_3() {     //  User Defined Control Software
  Selected_Other = Other_3_user; 
}
