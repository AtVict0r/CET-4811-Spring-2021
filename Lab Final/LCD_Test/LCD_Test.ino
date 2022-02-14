/*** header block ***
 * code file name: Test_Display_Output.ino
 * code description: Send data to an LCD display
 * hardware required: [UNO, USB Cable, Breadboard, Jumper Wires, 16x2 LCD Display, 10k ohms Resistor]
 * IDE version used to test code: 1.8.13
 * programmer(s) name: Oluwasegun Atolagbe
 * date when code is created/modified: 17/02/2021
 * code version: 1.0
 ***/

// pre-processor directives
// include the library code:
#include <LiquidCrystal.h>

// pin name definitions
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int d4 = 2, d5 = 3, d6 = 4, d7 = 7, en = 8, rs = 12;

// class/object declarations
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
   // code that runs only once 
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // data processing   
   // data output
   
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
