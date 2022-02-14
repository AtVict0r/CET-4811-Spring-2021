const int analogPin = A0;
const int analogOutPin = 9;

int prevOut;

void setup()
{
  pinMode(9, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(analogPin);
  int outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  analogWrite(analogOutPin, outputValue);
  
  if(prevOut != outputValue)
  {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
    
    prevOut = outputValue;
   }
  
  delay(10);
}