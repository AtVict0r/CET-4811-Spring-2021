#include <Servo.h>

Servo myservo1, myservo2, myservo3, myservo4;  // create servo object to control a servo

void setup() {
  myservo1.attach(6);  // attaches the servo 1 on pin 6 to the servo object
  myservo2.attach(9);  // attaches the servo 2 on pin 6 to the servo object
  myservo3.attach(10);  // attaches the servo 3 on pin 6 to the servo object
  myservo4.attach(11);  // attaches the servo 4 on pin 6 to the servo object
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 1023)
  int val1 = analogRead(A0);
  int val2 = analogRead(A1);
  int val3 = analogRead(A2);
  int val4 = analogRead(A3);
  
  // scale it to use it with the servo
  val1 = map(val1, 0, 1023, 0, 180);     // value between 0 and 180)
  val2 = map(val2, 0, 1023, 70, 180);     // value between 0 and 180)
  val3 = map(val3, 0, 1023, 25, 125);     // value between 0 and 180)
  val4 = map(val4, 0, 1023, 25, 70);     // value between 0 and 180)
  
  // sets the servo position according to the scaled value
  myservo1.write(val1);
  myservo2.write(val2);
  myservo3.write(val3);
  myservo4.write(val4);
                    
  delay(15);                           // waits for the servo to get there
}
