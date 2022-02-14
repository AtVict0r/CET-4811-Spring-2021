/*** header block ***
 * code file name: Test_Analog_IO.ino
 * code description: Use a potentiometer to control brightness of an led
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, Potentiometer, LED, 330 ohms Resistor]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives

// pin name definitions
const int led = 9;

// class/object declarations

// global variables
const int fadeAmount = 5;
int prevBrightness = 0;

void setup () {
   // configure hardware peripherals
   pinMode(led, OUTPUT);

   // configure data communication
   Serial.begin(9600);

   // code that runs only once 
}

void loop () {
   // data storage
   // data input
   int sensorValue = analogRead(A0);
   
   // data processing
   int brightness = map(sensorValue, 0, 1023, 0, 255);
      
   // data output
   analogWrite(led, brightness);
   
   // data communication
   if(brightness != prevBrightness)
   {
      Serial.println(sensorValue);
      prevBrightness = brightness;
   }

   delay(30);
}

// user defined functions

