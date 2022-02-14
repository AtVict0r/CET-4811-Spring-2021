/*** header block ***
 * code file name: Test_Robot_Arm.ino
 * code description: Control a robot arm using an analog and advanced sensor
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, Push Button, LED, 10k ohms Resistor, 330 ohms Resistor,
					   1K Potentiometer, 16x2 LCD Display, Servo motor, IR Receiver, Remote]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives
#include "IRremote.h"
#include <Servo.h>
#include <LiquidCrystal.h>

// pin name definitions
const int button = 13, receiver = 5,
          servo1 = 6, servo2 = 9, servo3 = 10, servo4 = 11, /** SERVO PWN Pins **/
          d4 = 2, d5 = 3, d6 = 4, d7 = 7, en = 8, rs = 12; /** LCD Pins **/

// class/object declarations
IRrecv remote(receiver);  // create instance of 'remote'
// with signal pin of IR receiver to Arduino Digital PWM Pin 5
decode_results code; // create instance of 'decode_results'
Servo myservo1, myservo2, myservo3, myservo4;  // create servo object to control servos
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // create lcd object to send data to lcd
		  
// global variables
const int m1n[] = {0, 75, 25, 25}, m4x[] = {180, 180, 125, 70}; /** Min and Max value for servos **/
int p0s = 0, servoP0s[] = {0, 75, 25, 25}, amp[] = {3, 3, 3, 3};
bool p0wer = 1, m0de = 1;

void setup() {
   // configure data communication
  Serial.begin(9600); Serial.println("--> Start <--");

   // code that runs only once 
  remote.enableIRIn(); // Start the receiver

  myservo1.attach(servo1); myservo2.attach(servo2); myservo3.attach(servo3); myservo4.attach(servo4);
  myservo1.write(m1n[0]); myservo2.write(m4x[1]); myservo3.write(m1n[2]); myservo4.write(m1n[3]);

  lcd.begin(16, 2); lcd.print("****************");
  delay(1000);
  lcd.clear(); lcd.print("--> Start <--");
}

void loop() {
  // data processing
  power();

  if (m0de) {
    potControl();

    if (remote.decode(&code) && (code.value == 0xFF629D)) { // have we received an IR signal?
      m0de = !m0de;
      remote.resume(); // receive the next value
    }
  } else {
    if (remote.decode(&code)) { // have we received an IR signal?
      irControl();
      remote.resume(); // receive the next value
    }
  }
  
  // data output
  sendLCD();

   // data communication
  sendSerial();

  delay(1000);
}

// user defined functions
char translateIR() {  // takes action based on IR code received
  switch (code.value) { // describing Remote IR codes
    case 0xFFA25D: return '-';
    case 0xFFE21D: return '+';
    case 0xFF629D: return 'C';
    case 0xFF22DD: return '<';
    case 0xFF02FD: return '>';
    case 0xFFC23D: return 'P';
    case 0xFFE01F: return '(';
    case 0xFFA857: return ')';
    case 0xFF30CF: return '1';
    case 0xFF18E7: return '2';
    case 0xFF7A85: return '3';
    case 0xFF10EF: return '4';
    case 0xFFFFFFFF: break;
    default: return 'I';
  }

  delay(500);
}

void power() {
  delay(2);

  if (digitalRead(button)) {
    if (p0wer) {
      lcd.display();
    }
    else {
      lcd.noDisplay();
    }
  } else {
    lcd.noDisplay();
  }
}

void sendSerial() {
  Serial.print("\nPower: ");
  Serial.print(p0wer);
  Serial.print("\tMode: ");
  Serial.println(m0de);

  for (int i = 0; i < 4; i++) {
    Serial.print("Servo: ");
    Serial.println(i + 1);

    Serial.print("Position: ");
    Serial.print(m1n[i]);
    Serial.print(" / ");
    Serial.print(servoP0s[i]);
    Serial.print(" / ");
    Serial.println(m4x[i]);

    Serial.print("Amplitude: ");
    Serial.println(amp[i]);
  }

  delay(25);
}

void sendLCD() {
  lcd.clear();

  lcd.setCursor(0, 0);
  if (!m0de) {
    lcd.print("Servo: ");
    lcd.print(p0s + 1);
    lcd.print(" Amp: ");
    lcd.print(amp[p0s]);
  } else {
    lcd.print("Using ANALOG IN");
  }

  lcd.setCursor(0, 1);
  if (!m0de) {
    lcd.print("IR ");
  };
  lcd.print("Pos: ");
  lcd.print(servoP0s[p0s]);
  lcd.print("/");
  lcd.print(m4x[p0s]);

  delay(25);
}

void irControl() {  // takes action based on IR code received
  switch (translateIR()) {
    case '-': if (p0s > 0) {
        p0s--;
      } break;
    case '+': if (p0s < 3) {
        p0s++;
      } break;
    case 'C': m0de = !m0de; break;
    case '<': if (servoP0s[p0s] > m1n[p0s]) {
        servoP0s[p0s] -= amp[p0s];
      } break;
    case '>': if (servoP0s[p0s] < m4x[p0s]) {
        servoP0s[p0s] += amp[p0s];
      } break;
    case 'P': p0wer = !p0wer; break;
    case '(': if (amp[p0s] > 3) {
        amp[p0s]--;
      } break;
    case ')': if (amp[p0s] < 10) {
        amp[p0s]++;
      } break;
    case '1': p0s = 0;
    case '2': p0s = 1;
    case '3': p0s = 2;
    case '4': p0s = 3;
    case 'I': Serial.println("\n  Invalid Option  !!!");
      lcd.clear(); lcd.home(); lcd.print(" Invalid Option ");
      delay(1000);
  }

  switch (p0s) {
    case 0: myservo1.write(servoP0s[p0s]); break;
    case 1: myservo2.write(servoP0s[p0s]); break;
    case 2: myservo3.write(servoP0s[p0s]); break;
    case 3: myservo4.write(servoP0s[p0s]); break;
  }

  delay(50);
}

void potControl() {
  int analogValue[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3)};

  for (int i = 0; i < 4; i++) {
    // scale it to use it with the servo
    servoP0s[i] = map(analogValue[i], 0, 1023, m1n[i], m4x[i]);

    delay(5);

    switch (i) { // sets the servo position according to the scaled value
      case 0: myservo1.write(servoP0s[i]); break;
      case 1: myservo2.write(servoP0s[i]); break;
      case 2: myservo3.write(servoP0s[i]); break;
      case 3: myservo4.write(servoP0s[i]); break;
    }

    delay(50);
  }
}
