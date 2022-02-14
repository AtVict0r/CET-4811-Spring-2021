#include "IRremote.h"
#include <Servo.h>

IRrecv remote(5);  // create instance of 'remote' 
                   // with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'
Servo myservo;  // create servo object to control a servo

int pos = 0, amp = 1;

char translateIR() {  // takes action based on IR code received
  char message;
  
   switch (code.value) { // describing Remote IR codes
    case 0xFF22DD: message = '<'; break;
    case 0xFF02FD: message = '>'; break;
    case 0xFFE01F: message = '('; break;
    case 0xFFA857: message = ')'; break;
    case 0xFFFFFFFF: break;
    default: message = 'I';
  }

  delay(500); return message;
}

void irControl() {  // takes action based on IR code received  
   switch (translateIR()) {
    case '<': if(pos > 0){ pos -= amp; } break;
    case '>': if(pos < 180){ pos += amp; } break;
    case '(': if(amp > 1){ amp--; } break;
    case ')': if(amp < 10){ amp++; } break;
    case 'I': Serial.println("Invalid Option");
  }

  myservo.write(pos);

  Serial.println("/nServo: ");
  Serial.print("Position: ");
  Serial.print(pos);
  Serial.print("/tAmplitude: ");
  Serial.println(amp);
  
  delay(500);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  remote.enableIRIn(); // Start the receiver
  myservo.attach(6);  // attaches the servo on pin 6 to the servo object
}

void loop() {
  if (remote.decode(&code)) { // have we received an IR signal?
    irControl();
    remote.resume(); // receive the next value
  }
}
