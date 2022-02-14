/* Ping))) Sensor
  
   This program reads a HC-SR04 ultrasonic rangefinder (URF) and returns 
   the distance to the closest object in range. To do this, it sends 
   a pulse to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
	* Vcc  connection of the HC-SR04 attached to +5V
        * Echo connection of the HC-SR04 attached to A0
        * Trig connection of the HC-SR04 attached to A1
	* Gnd  connection of the HC-SR04 attached to ground

   Created   3 Nov 2008 by David A. Mellis
   Modified 30 Aug 2011 by Tom Igoe
   Modified 12 Jan 2013 by F. Zia to implement HC-SR04 4-pin interface
   Modified 03 Mar 2021 by O. Atolagbe
   Part 2:
*/

// include the library code:
class RBG_LED 
{
  private:
  int redPin, bluePin,  greenPin;

  void on(int redLED, int blueLED, int greenLED) {
    digitalWrite(redPin, redLED);
    digitalWrite(bluePin, blueLED);
    digitalWrite(greenPin, greenLED);
  }

  public:
  RBG_LED(int rbgRedPin, int rbgBluePin, int rbgGreenPin){
    redPin = rbgRedPin;
    bluePin = rbgBluePin;
    greenPin = rbgGreenPin;
  }

  void begin() {
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
  }

  void off() {
    on(0, 0, 0);
  }

  void red() {
    on(1, 0, 0);
  }

  void blue() {
    on(0, 1, 0);
  }

  void green() {
    on(0, 0, 1);
  }

  void skyBlue() {
    on(0, 1, 1);
  }

  void yellow() {
    on(1, 0, 1);
  }

  void purple() {
    on(1, 1, 0);
  }

  void white() {
    on(1, 1, 1);
  }

  void testLED() {
    white();
    delay(500);
    yellow();
    delay(500);
    purple();
    delay(500);
    skyBlue();
    delay(500);
    green();
    delay(500);
    blue();
    delay(500);
    red();
    delay(500);
    off();
  }
};

// initialize the library with the numbers of the interface pins
RBG_LED rbg(11, 10, 9);

// Arduino pin numbers for the sensor output and input pins
const int pingEcho = A0, pingTrig = A1;

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // initialize sensor pins
  pinMode(pingEcho,  INPUT); // change A0 pin mode to digital input
  pinMode(pingTrig, OUTPUT); // change A1 pin mode to digital output

  rbg.begin();
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The HC-SR04 is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse
  digitalWrite(pingTrig,  LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrig,  LOW);

  // The Echo pin is used to read the signal from HC-SR04; a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(pingEcho, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  if (inches < 6)
  {
    rbg.red();
  } else if (inches > 12)
  {
    rbg.green();
  } else
  {
    rbg.yellow();
  }
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to the Ping sensor datasheet, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.

  return microseconds / 73.8 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return microseconds / 28.9 / 2;
}
