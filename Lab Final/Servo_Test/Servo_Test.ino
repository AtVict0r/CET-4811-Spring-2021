/***
 * code file name: Test_Motor_Output.ino
 * code description: Sweep the servo motor from 0 to 180
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, Servo motor]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives
#include <Servo.h>

// class/object declarations
Servo myservo1, myservo2, myservo3, myservo4;

void setup() {
   // code that runs only once 
  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);
}

void loop() {
  // data processing   
  // data output
  
  // Sweep from 0 to 180 degrees:
  for (int angle = 0; angle <= 180; angle++) {
    myservo1.write(angle);
    myservo2.write(angle);
    myservo3.write(angle);
    myservo4.write(angle);
    delay(30);
  }

  // And back from 180 to 0 degrees:
  for (int angle = 180; angle >= 0; angle--) {
    myservo1.write(angle);
    myservo2.write(angle);
    myservo3.write(angle);
    myservo4.write(angle);
    delay(30);
  }
  
  delay(500);
}