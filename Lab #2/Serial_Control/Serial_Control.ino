// FileName: Serial_Control
// Board:    Arduino Uno
// IDE:      Arduino 1.0
//
// F. Zia - 2011_1004, Updated: 2013_0213, 2018_0202
//
// read sensor value from analog input
// convert sensor value from 10-bits to 8-bits
// send sensor value to PC via serial port
//
// read command value from PC via serial port
// activate output device according to command value

void setup() {

  Serial.begin(9600);      // initialize serial port

  pinMode(12, OUTPUT);     // initialize pin 12 as digital output
  digitalWrite(12, LOW);   // initialize output device to be OFF
  
  pinMode(11, OUTPUT);     // initialize pin 11 as digital output
  digitalWrite(11, LOW);   // initialize output device to be OFF
  
  pinMode(13, OUTPUT);     // initialize pin 13 as digital output
}

void loop() {

  int  sensorVal;
  char command = 0;

  // Read sensor input value and send sensor value to PC

  sensorVal = analogRead(0);    // read sensor value from analog pin A0
  sensorVal = sensorVal >> 2;   // convert sensor value from 10-bits to 8-bits ...
  // by using bit shift operation

  Serial.println(sensorVal);    // send sensor value to PC

  // Read command keystroke from PC and control output device (LED)

  if (Serial.available())
    command = Serial.read();   // read command character from PC keyboard

  switch (command) {            // activate output device according to command

    case  '0':
      digitalWrite(12, LOW);  // turn output device OFF
      break;

    case  '1':
      digitalWrite(12, HIGH); // turn output device ON
      break;

    case  '2':
      digitalWrite(11, HIGH);  // turn output device OFF
      break;

    case  '3':
      digitalWrite(11, LOW); // turn output device ON
      break;

    default:
      // do nothing for other command values
      break;
  }

  // toggle pin 13 heartbeat LED to indicate that the code is running

  digitalWrite(13, HIGH); delay(100);
  digitalWrite(13, LOW);  delay(100);
}
