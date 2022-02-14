/*** header block ***
 * code file name: Test_Analog_IO.ino
 * code description: Read input from four potentiometers
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, 1K Potentiometer]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// global variables
const int sensorMin = 0, analogMax = 1023, digitalMax = 255;
int outputValue[4]; // value output to the PWM (analog out)

void setup() {
   // configure data communication
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // data storage
  // data input
  // read the analog input and store in variable sensor value:
  int sensorValue[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3)}; // value read from the pot
  
  // data processing 
  // map it to the range of the analog out:
  for(int i = 0; i < 4; i++) {
	  outputValue[i] = map(sensorValue[i], sensorMin, analogMax, sensorMin, digitalMax);
  }

   // data communication
  // print the results to the Serial Monitor:
  for(int i = 0; i < 4; i++) {
	  Serial.print("#");
	  Serial.println(i+1);
	  
	  Serial.print("sensor = ");
	  Serial.print(sensorValue[i]);
	  Serial.print("/");
	  Serial.println(analogMax);
	  
      Serial.print("output = ");
      Serial.print(outputValue[i]);
	  Serial.print("/");
	  Serial.println(digitalMax);
  }

  Serial.println();

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(1000);
}
