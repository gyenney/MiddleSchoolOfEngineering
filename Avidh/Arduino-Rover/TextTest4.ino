/*
STEM Center USA, Inc.
Pi-Bot: Motor Test Program using Function Calls
*/

#include <SoftwareSerial.h>

const int myRx = 7;  
const int myTx = 8;  

char inputBuffer[256];
SoftwareSerial mySerial(myRx, myTx);
void setup()
{
  mySerial.begin(19200);
  Serial.begin(19200);
 
  delay(1000);
  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");

}
void loop()
{

  if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage();
          break;
        default:
          break;
    }
  }  
}



void SendMessage()
{
  Serial.println("Sending message");
  mySerial.print("AT+CMGF=1\r");                                                        // AT command to send SMS message
  delay(100);
  mySerial.println("AT + CMGS = \"+18057015090\"");                                     // recipient's mobile number, in international format
  delay(100);
  mySerial.println("Hello from the Signal Light");        // message to send
  delay(100);
  mySerial.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  mySerial.println();
  delay(5000);          
}
