#include "IRremote.h"
#include <LiquidCrystal.h>

const int ir = 5; // IR receiver pin
const int d4 = 2, d5 = 3, d6 = 4, d7 = 7, en = 8, rs = 12; // LCD Pins

IRrecv remote(ir);  // create instance of 'remote' 
                   // with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char translateIR() {  // takes action based on IR code received
  char message;
  
   switch (code.value) { // describing Remote IR codes
    case 0xFFA25D: message = '-'; break;
    case 0xFFE21D: message = '+'; break;
    case 0xFF629D: message = 'C'; break;
    case 0xFF22DD: message = '<'; break;
    case 0xFF02FD: message = '>'; break;
    case 0xFFC23D: message = 'P'; break;
    case 0xFFE01F: message = '('; break;
    case 0xFFA857: message = ')'; break;
    case 0xFF30CF: message = '1'; break;
    case 0xFF18E7: message = '2'; break;
    case 0xFF7A85: message = '3'; break;
    case 0xFF10EF: message = '4'; break;
    case 0xFFFFFFFF: break;
    default: message = 'I';
  }

  delay(500); return message;
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  lcd.begin(16, 2);
  remote.enableIRIn(); // Start the receiver
   lcd.print("Code: ");
}

void loop() {
  if (remote.decode(&code)) { // have we received an IR signal?
    lcd.setCursor(0, 1);
    lcd.print(translateIR());
    remote.resume(); // receive the next value
  }
}
