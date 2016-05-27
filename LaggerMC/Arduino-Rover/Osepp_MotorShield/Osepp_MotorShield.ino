const int Motor0A = 6;  
const int Motor0B = 5;   
const int Motor1A = 9;  
const int Motor1B = 10; 
const int Motor2A = 11;  
const int Motor2B = 3; 
const int DIR_EN = 7;
const int Dir_Latch = 12;
const int Dir_Ser = 8;
const int Dir_Clk = 4;



void setup() 
{
  // initialize the pins
  pinMode(Motor0A,OUTPUT);
  pinMode(Motor0B, OUTPUT);
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2A,OUTPUT);
  pinMode(Motor2B, OUTPUT);
  pinMode(DIR_EN, OUTPUT);
  pinMode(Dir_Latch, OUTPUT);
  pinMode(Dir_Ser, OUTPUT);
  pinMode(Dir_Clk, OUTPUT);

  Serial.begin(19200);
}

void loop()
{
  digitalWrite(DIR_EN, 1);
  digitalWrite(Dir_Latch, 1);  
  digitalWrite(Dir_Ser, 1);
  analogWrite(Motor0A, 128);
  analogWrite(Motor0B, 128);
  analogWrite(Motor1A, 128);
  analogWrite(Motor1B, 128);
  analogWrite(Motor2A, 128);
  analogWrite(Motor2B, 128);

}


