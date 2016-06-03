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
const int northInputSensor = 0; //goes to pin A0 on the Arduino
const int eastInputSensor = 1; //goes to pin A1 on the Arduino
const int northOutputSensor = 2;
const int eastOutputSensor = 3;

//phone number of the smart rover
const int phoneNumber = 8051234567;//TODO: implement this number instead of a magic 
                                   //phone number in code


//SOFTWARE CONSTANTS
const int threshold = 100; //this threshold determines if the car is present or not


//DYNAMIC SOFTWARE VARIABLES



bool hasStopped = false;          //determines if the estop message has been sent
                                  //before sending another estop message, prevents
                                  //spamming
bool hasCleared = false; //see above, this one determines if the all clear message has been sent

bool north = false;

bool east = false;

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
  pinMode(northInputSensor, INPUT); //declaring both sensore as inputs
  pinMode(eastInputSensor, INPUT);

  
  pinMode(northOutputSensor, INPUT); //declaring both sensore as inputs
  pinMode(eastOutputSensor, INPUT);

  

  //LEDs:
  pinMode(northGreenLed, OUTPUT);  //declaring all of the led's as outputs
  pinMode(eastGreenLed, OUTPUT);
  
  pinMode(eastGreenLed, OUTPUT);
  pinMode(eastRedLed, OUTPUT);

  //Serial Initialization:
  TextModuleComms.begin(19200); //begin the Serial communication with the GSM module
  Serial.begin(19200); //begin the standard Serial Communication with the computer
  
  delay(100); //wait for the Serial to start?
  
  TextModuleComms.println("AT+IPR=19200"); //tell the GSM Module your baud rate?
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
  if (isEastPresent()){
    if(isNorthPresent()){
      if(hasStopped == false){
        Serial.println("COLLISION IMMINENT: ACTIVATING EMERGENCY STOP");
        SendMessage("EMERGENCY_STOP");

        setNorthLight(false);
        setEastLight(false);

        hasStopped = true;
        hasCleared = false;
      }
      
    }else{
      setNorthLight(false);
      setEastLight(true);
    }
  }else{
    setNorthLight(true);
    setEastLight(false);
  }
//  if (hasStopped == true){
//    if(isEastPresent() == false){
//      if(isNorthPresent() == false){
//        hasStopped = false;
//      }else if(isNorthPresent() == true){
//        if(hasCleared == false){
//          SendMessage("All_Clear");
//          hasStopped = false;
//          hasCleared = true;
//        }
//      }
//    }
   if (hasCleared == false){
      if(hasStopped == true){
        if(!isEastPresent()){
         SendMessage("All_Clear");
         hasCleared = true;
         hasStopped = false;
        }
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
}

boolean isNorthPresent(){
  if(isNorthInputPresent()){
    north = true;
  }
  if(isNorthOutputPresent()){
    north = false;
  }
  return north;
}
boolean isEastPresent(){
  if(isEastInputPresent()){
    east = true;
  }
  if(isEastOutputPresent()){
    east = false;
  }
  return east;
}


boolean isEastInputPresent(){
  if (analogRead(eastInputSensor) < threshold){
    return true;
  }else{
    return false;
  }
}
//returns if the northbound car is approaching the intersection
boolean isNorthInputPresent(){
  if (analogRead(northInputSensor) < threshold){
    return true;
  }else{
    return false;
  }
}
boolean isEastOutputPresent(){
  if (analogRead(eastOutputSensor) < threshold){
    return true;
  }else{
    return false;
  }
}
boolean isNorthOutputPresent(){
  if (analogRead(eastOutputSensor) < threshold){
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
void SendMessage(String input)
{
  Serial.println("---------> " + input + "<----------");
  Serial.println("Sending message");
  TextModuleComms.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(100);
  TextModuleComms.println("AT + CMGS = \"+18052647095\"");                                     // recipient's mobile number, in international format
  delay(100);
  TextModuleComms.println(input);        // message to send
  delay(100);
  TextModuleComms.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  TextModuleComms.println();
  delay(5000);          
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
