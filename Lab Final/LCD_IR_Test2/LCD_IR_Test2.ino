#include "IRremote.h"
#include <LiquidCrystal.h>

const int ir = 5; // IR receiver pin
const int d4 = 2, d5 = 3, d6 = 4, d7 = 7, en = 8, rs = 12; // LCD Pins

IRrecv remote(ir);  // create instance of 'remote' 
                   // with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int p0s = 0;
char serv0 = '0';
bool p0wer = 0;

char translateIR() {  // takes action based on IR code received
  char message;
  
   switch (code.value) { // describing Remote IR codes
    case 0xFFA25D: message = '-'; break;
    case 0xFFE21D: message = '+'; break;
    case 0xFF629D: message = 'C'; break;
    case 0xFF22DD: message = '<'; break;
    case 0xFF02FD: message = '>'; break;
    case 0xFFC23D: message = 'P'; break;
    case 0xFF30CF: message = '1'; break;
    case 0xFF18E7: message = '2'; break;
    case 0xFF7A85: message = '3'; break;
    case 0xFF10EF: message = '4'; break;
    case 0xFFFFFFFF: break;
    default: message = 'I';
  }

  delay(500); return message;
}

void irControl() {  // takes action based on IR code received  
   switch (translateIR()) {
    case '-': if(serv0 > '1'){ serv0--; } break;
    case '+': if(serv0 < '4'){ serv0++; } break;
    case 'C': break;
    case '<': if(p0s > 0){ p0s--; } break;
    case '>': if(p0s < 180){ p0s++; } break;
    case 'P': if(p0wer){ lcd.display(); } 
              else { lcd.noDisplay(); }
              p0wer = !p0wer; break;
    case '1': serv0 = '1'; break;
    case '2': serv0 = '2'; break;
    case '3': serv0 = '3'; break;
    case '4': serv0 = '4'; break;
    default: lcd.clear(); lcd.home(); lcd.print("Invalid Option"); delay(500);
  }

  lcd.clear();
  lcd.home(); lcd.print("Servo: "); lcd.print(serv0);
  lcd.setCursor(0, 1); lcd.print(p0s);

  delay(500);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  lcd.begin(16, 2);
  remote.enableIRIn(); // Start the receiver
  lcd.print("Servo: ");
}

void loop() {
  if (remote.decode(&code)) { // have we received an IR signal?
    irControl();
    remote.resume(); // receive the next value
  }
}
