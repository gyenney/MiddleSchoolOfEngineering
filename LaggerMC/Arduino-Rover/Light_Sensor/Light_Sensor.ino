/*
MiddleSchoolOfEngineering

Light_Sensor

Greg Yenney

*/

const int lightSensor1 = 0;
const int lightSensor2 = 1;

int light_level1;
int light_on1;

int light_level2;
int light_on2;


void setup()
{
  pinMode(lightSensor1, INPUT);
  pinMode(lightSensor2, INPUT);
  Serial.begin(19200);
}


void loop()
{
  light_level1 = analogRead(lightSensor1);
  light_level2 = analogRead(lightSensor2);
  
  Serial.print("Light Level1:  ");
  Serial.print(light_level1);
  Serial.println();
 

  if (light_level1 > 100)
  {
      if (light_on1 == 0)
      {
          light_on1 = 1;
          Serial.println("Light1 was turned on!");
      }
  }
  else
  {
      if (light_on1 == 1)
      {
          light_on1 = 0;
          Serial.println("Light1 was turned off!");
      }
  }

  
  Serial.print("Light Level2:  ");
  Serial.print(light_level2);
  Serial.println();
 

  if (light_level2 > 100)
  {
      if (light_on2 == 0)
      {
          light_on2 = 1;
          Serial.println("Light was turned on!");
      }
  }
  else
  {
      if (light_on2 == 1)
      {
          light_on2 = 0;
          Serial.println("Light was turned off!");
      }
  }

  
  delay(300);
  
}
 
