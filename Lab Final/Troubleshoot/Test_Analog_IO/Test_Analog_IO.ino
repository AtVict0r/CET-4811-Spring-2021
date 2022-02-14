int prevBrightness;

void setup () 
{
   // configure data communication
   Serial.begin(9600);
}

void loop () 
{
   int sensorValue = analogRead(A3);
   
   // data processing
   int brightness = map(sensorValue, 0, 1023, 0, 255);
   
   // data communication
   if(prevBrightness != brightness)
   {
      Serial.print("Analog Input: ");
      Serial.print(sensorValue);
      Serial.println("/1024");
  
      Serial.print("Digital Output: ");
      Serial.print(brightness);
      Serial.println("/255");

      Serial.println();

      prevBrightness = brightness;
   }

   delay(2);
}
