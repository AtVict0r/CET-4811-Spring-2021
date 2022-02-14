/*** header block ***
 * code file name: Test_Advanced_Sensor.ino
 * code description: Read input from an IR receiver
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, IR transistor, 10k ohms Resistor, IR Remote]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives
#include "IRremote.h"

// class/object declarations
IRrecv remote(5);  // create instance of 'remote' 
                   // with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'

void setup() {
   // configure data communication
  Serial.begin(9600);
  
   // code that runs only once 
  Serial.println("IR Receiver Button Decode");
  remote.enableIRIn(); // Start the receiver
}

void loop() {
  if (remote.decode(&code)) { // have we received an IR signal?
    // data communication
    Serial.print("Code: ");
    Serial.println(translateIR()); // return char_type to the Serial Monitor
	
    remote.resume(); // receive the next value
  }
}

// user defined functions
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
