/* This code is very similar to the original SMS_x_controller
 *  and includes many of the same elements (#CopyAndPasteForDays)
 *  I have edited it to be more effecient and easy to read
 *  (Also, I was having a hard time understanding the other code
 *  so this will take me through it step-by-step
 *  
 *  Author: Mr. Yenney, Avidh, Jay
 */
#include <SoftwareSerial.h>


//CONSTANTS

//ELECTRICAL CONSTANTS
//these pins are used to transmit data back and forth between the cell module
//and the Arduino:
const int RXPin = 7; //pin 7 on the arduino goes to 7 on the GSM module (reciever)
const int TXPin = 8; //pin 8 on the arduino goes to 8 on the GSM module (transmitter)

//these are just some led pinouts:
const int northRedLed = 11;
const int northGreenLed = 10;

const int eastGreenLed = 12;
const int eastRedLed = 13;

//these are the light sensors that will be used to detect approaching vehicles:
const int northSensor = 0; //goes to pin A0 on the Arduino
const int eastSensor = 1; //goes to pin A1 on the Arduino

//phone number of the smart rover
const int phoneNumber = 8051234567;//TODO: implement this number instead of a magic 
                                   //phone number in code


//SOFTWARE CONSTANTS
const int threshold = 100; //this threshold determines if the car is present or not


//DYNAMIC SOFTWARE VARIABLES
double northLightLevel = 0;
double eastLightLevel = 0;

char inputBuffer[256]; //what does this do?

SoftwareSerial TextModuleComms(RXPin, TXPin); //ties the rx and tx pins 
                                                      //to a Serial object
                                                      //used to communicate with 
                                                      //the GSM module
void setup() {

  //PIN ASSIGNMENTS:
  
  //Serial Pins:
  pinMode(RXPin, INPUT_PULLUP); //declaring the reciever pin as an input
  pinMode(TXPin, OUTPUT); //declaring the transmitter pin as an output

  //Sensors:
  pinMode(northSensor, INPUT); //declaring both sensore as inputs
  pinMode(eastSensor, INPUT);

  //LEDs:
  pinMode(northGreenLed, OUTPUT);  //declaring all of the led's as outputs
  pinMode(eastGreenLed, OUTPUT);
  
  pinMode(eastGreenLed, OUTPUT);
  pinMode(eastRedLed, OUTPUT);

  //Serial Initialization:
  TextModuleComms.begin(250000); //begin the Serial communication with the GSM module
  Serial.begin(250000); //begin the standard Serial Communication with the computer
  
  delay(100); //wait for the Serial to start?
  
  TextModuleComms.println("AT+IPR=250000"); //tell the GSM Module your baud rate?
  delay(1000); //wait for the GSM module
  TextModuleComms.println("AT+CMGF=1"); //sets the GSM Module in text mode
  
  
  //Testing Sequence: 
  Serial.println("Test Signal: Green"); //tell the user the lights are turning green
  setNorthLight(true);  //turn the lights green
  setEastLight(true);
  delay(1000);  //wait for the user to see the lights
  Serial.println("Test Signal: Red"); //tell the user the lights are turning red
  setNorthLight(false); //turn the lights red
  setEastLight(false);
  delay(1000);  //wait for the user to see the lights
  Serial.println("Done"); //tell the user the sequence has completed


  //Initialization Sequence:
  Serial.println("Initializing, remove vehicles from the intersection"); 
  while (!isEastPresent && !isNorthPresent){
    Serial.println("Light Not Detected");
    delay(500);
  }
  Serial.println("Initialization Complete: Light Detected");
}

void loop() {
//  if (isEastPresent()){
//    if(isNorthPresent()){
//      Serial.println("COLLISION IMMINENT: ACTIVATING EMERGENCY STOP");
//      SendMessage("EMERGENCY_STOP");
//
//      setNorthLight(false);
//      setEastLight(false);
//      
//    }else{
//      setNorthLight(false);
//      setEastLight(true);
//    }
//  }else{
//    setNorthLight(true);
//    setEastLight(false);
//  }
SendMessage("Hello World");
if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage("Hello from the Signal Light");
          break;
        default:
          break;
    }
  }
  for (int i = 0 ; i < 256 ; i++)
  {
      inputBuffer[i] = 0;
  }
  if (TextModuleComms.available()>0)
  {
      TextModuleComms.readBytes(inputBuffer, 255);
      Serial.write(inputBuffer);
  }   
  delay(30000);
}

//returns if the eastbound car is approaching the intersection
boolean isEastPresent(){
  if (analogRead(eastSensor) < threshold){
    return true;
  }else{
    return false;
  }
}
//returns if the northbound car is approaching the intersection
boolean isNorthPresent(){
  if (analogRead(northSensor) < threshold){
    return true;
  }else{
    return false;
  }
}


//sets the North Stoplights state, if true is passed, it turns it green, else
//it turns it red
void setNorthLight(boolean on){
  if (on){
    digitalWrite(northRedLed, LOW);
    digitalWrite(northGreenLed, HIGH);
  }else{
    digitalWrite(northRedLed, HIGH);
    digitalWrite(northGreenLed, LOW);
  }
}
void SendMessage(String message)
{
  Serial.println("SendMessage()");
  TextModuleComms.println("AT+CMGS=\"8057015090\"\r"); // Replace x with mobile number
  delay(100);
  TextModuleComms.print("<Signal_Message=");// The SMS text you want to send
  delay(100);
  TextModuleComms.print(message);
  delay(100);
  TextModuleComms.println(">");
  TextModuleComms.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}



//sets the East Stoplights state, if true is passed, it turns it green, else
//it turns it red
void setEastLight(boolean on){
  if (on){
    digitalWrite(eastRedLed, LOW);
    digitalWrite(eastGreenLed, HIGH);
  }else{
    digitalWrite(eastRedLed, HIGH);
    digitalWrite(eastGreenLed, LOW);
  }
}
