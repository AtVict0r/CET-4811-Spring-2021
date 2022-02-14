#include "IRremote.h"
#include <Servo.h>

IRrecv remote(5);  // create instance of 'remote' 
                   // with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'
Servo myservo1, myservo2, myservo3, myservo4;  // create servo object to control servos 

const int m1n[] = {0, 75, 25, 25}, m4x[] = {180, 180, 125, 70};
int servoP0s[] = {0, 75, 25, 25}, amp[] = {3, 3, 3, 3}, p0s = 0;

char translateIR() {  // takes action based on IR code received
  char message;
  
   switch (code.value) { // describing Remote IR codes
    case 0xFFA25D: message = '-'; break;
    case 0xFFE21D: message = '+'; break;
    case 0xFF22DD: message = '<'; break;
    case 0xFF02FD: message = '>'; break;
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

void irControl() {  // takes action based on IR code received  
   switch (translateIR()) {
    case '-': if(p0s > 0){ p0s--; } break;
    case '+': if(p0s < 3){ p0s++; } break;
    case '<': if(servoP0s[p0s] > m1n[p0s]){ servoP0s[p0s] -= amp[p0s]; } break;
    case '>': if(servoP0s[p0s] < m4x[p0s]){ servoP0s[p0s] += amp[p0s]; } break;
    case '(': if(amp[p0s] > 3){ amp[p0s]--; } break;
    case ')': if(amp[p0s] < 10){ amp[p0s]++; } break;
    case '1': p0s = 0;
    case '2': p0s = 1;
    case '3': p0s = 2;
    case '4': p0s = 3;
    case 'I': Serial.println("\n  Invalid Option  !!!");
  }

  switch (p0s) {
    case 0: myservo1.write(servoP0s[p0s]); break;
    case 1: myservo2.write(servoP0s[p0s]); break;
    case 2: myservo3.write(servoP0s[p0s]); break;
    case 3: myservo4.write(servoP0s[p0s]); break;
  }

  Serial.print("\nServo: ");
  Serial.println(p0s + 1);
  Serial.print("Position: ");
  Serial.print(servoP0s[p0s]);
  Serial.print("\tAmplitude: ");
  Serial.println(amp[p0s]);
  
  delay(500);
}

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  remote.enableIRIn(); // Start the receiver  
  myservo1.attach(6); myservo2.attach(9); myservo3.attach(10); myservo4.attach(11);
  myservo1.write(m1n[0]); myservo2.write(m1n[1]); myservo3.write(m1n[2]); myservo4.write(m1n[3]);
}

void loop() {
  if (remote.decode(&code)) { // have we received an IR signal?
    irControl();
    remote.resume(); // receive the next value
  }
}
