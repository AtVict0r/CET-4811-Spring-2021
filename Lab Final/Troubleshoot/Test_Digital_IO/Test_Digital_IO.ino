/*** header block ***
 * code file name: Test_Digital_IO.ino
 * code description: Use a digital switch to control an led
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, Push Button, LED, 10k ohms Resistor, 330 ohms Resistor]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives

// pin name definitions
const int pushButton = 2;
          led = 13;

// class/object declarations

// global variables
bool prevState;

void setup () {
   // configure hardware peripherals
   pinMode(pushButton, INPUT);
   pinMode(led, OUTPUT);

   // configure data communication
   Serial.begin(9600);

   // code that runs only once 
   prevState = digitalRead(pushButton);
}

void loop () {
   // data storage
   // data input
   bool buttonState = !digitalRead(pushButton);
   
   // data processing   
   // data output
   buttonState ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);
   
   // data communication
   if(buttonState != prevState)
   {
      Serial.println(buttonState);
      prevState = buttonState;
   }
}

// user defined functions

