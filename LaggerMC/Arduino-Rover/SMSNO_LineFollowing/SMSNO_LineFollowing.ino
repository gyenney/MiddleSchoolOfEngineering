// MiddleSchoolOfEngineering
//
// Authors:  Greg Yenney, Sean Siddens, Jake Yenney
// 
// Based on StemCenterUSA: LineFollowing

/*
#include <SoftwareSerial.h> 

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2


char inputBuffer[256];
int commandValue = -1;


SoftwareSerial mySerial(myRx, myTx);
*/

const int Line1 = 10;     // was 7 Left Line Sensor
const int Line2 = 12;     // was 8 Center Line Sensor
const int Line3 = 13;     // was 10 Right Sensor 

const int In1 = 3;      // In1
const int In2 = 5;      // In2
const int In3 = 6;     // In3
const int In4 = 11;     // In4


// NO SMS, goFlag must be true
boolean   goFlag = true;

/*
boolean   turnLeftFlag = false;
boolean   turnRightFlag = false;
*/

void setup() 
{
  // initialize the pins

  /*
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);
  */
  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT); 
  pinMode(Line1, INPUT); 
  pinMode(Line2, INPUT); 
  pinMode(Line3, INPUT); 
  

  /*
  mySerial.begin(19200);
  */
  
  Serial.begin(19200);
  
  
  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");
 

  
}

void loop()
{
  int slow, fast;
  int speed1;
  int speed2;

  //int speedFactor = .5;
  //// fast = 100
  //fast=75;
  //slow=0;


  // Original
  //fast=40;
  //slow=0;
  fast=35;
  slow=0;

  
  int L1;
  int L2;
  int L3;
  int dir;
  while(1==1)
  {

    /*
    if (Serial.available() > 0)
    {
      switch(Serial.read())
      {
        case 's':
          Serial.println("Send Message.");
          SendMessage("Hello, from the SMS_car_controller!");
          break;
            
        case 't':
          Serial.println("Sending.");
          SendMessage("Hi");
          break;

        default:
          break;
      }
    }


    if (mySerial.available()>0)
    {
      mySerial.readBytes(inputBuffer, 255);

      // print the original data that came in from the txt.
      //
      Serial.println();
      Serial.println("ORIGINAL_DATA: ");
      Serial.write(inputBuffer);
      Serial.println("ORIGINAL_DATA_END");
      // send the message to processTxt function which will read the txt to determine info:
      //    The phone number of sender 
      //    The txt message itself
      // processTxt gets the message in order to determine action for car.
      // 
      commandValue = processTxt(inputBuffer, sizeof(inputBuffer));
    }   

    for (int j = 0 ; j < 256 ; j++)
    {
        inputBuffer[j] = 0;
    }

  
    // take appropriate action based on the command that was returned.
    
    
    
    if (commandValue != -1)
    { 
    
      switch(commandValue)
      {
        case 1:
          Serial.println("GO-ing");
          forward(speed1, speed2);
          goFlag = true;
          turnLeftFlag = false;
          turnRightFlag = false;
          break;
          
           
        case 2:
          Serial.println("STOP-ing.");
          //stopNow();
          forward(0,0);
          goFlag = false;
          turnLeftFlag = false;
          turnRightFlag = false;
          break;

        case 3:
          Serial.println("Turning Left");
          turnLeftFlag = true;
          break;

        case 4:
          Serial.println("Turning Right");
          turnRightFlag = true;
          break;

        
        case 99:
          Serial.println("Sending status.");
          SendMessage("STATUS MSG");
          break;
        
        default:
          break;
           
      }
      Serial.print("Command is: ");
      Serial.println(commandValue);
      commandValue = -1;
    }
    
    */



    if (goFlag)
    {
    
        L1 = digitalRead(Line1);
        L2 = digitalRead(Line2);
        L3 = digitalRead(Line3);
        Serial.print(L1);
        Serial.print(", ");
        Serial.print(L2);
        Serial.print(", ");
        Serial.println(L3); 
    
        //if(L1 == 1 & L2 == 0 & L3 == 0)
        if(L1 == 1 & L3 == 0)  // this navigates thick lines better.
        {
            //Left sees black, center & right see white
            //Turn left
            dir = 1;
            speed1=slow;
            speed2=fast;
            //forward(speed1, speed2);
        }
        else if (L1 == 0  & L2 == 0 & L3 == 0)  // was 1, 1, 1
        {
            //All sensors see white, All LEDs are on
            // Off the track or line is between sensors.
            speed1=30;
            speed2=30;
            //forward(speed1, speed2);
        }
        else if (L1 == 0 & L2 == 1 & L3 == 0)
        {
            //left sees white, center black and right white
            // left LED is on, center LED is off, right LED is on
            //go forward fast
            //speed1=40;
            //speed2=35;
            speed1=35;
            speed2=30;
            //forward(speed1, speed2);
        }
        else if (L1 == 1 & L2 == 1 & L3 == 1)  // was 0, 0, 0, 
        {
            //All sensors see black, All LEDs are off
            //go forward fast
            //speed1=40;
            //speed2=35;
            /*
            if (turnLeftFlag)
            {
                turnLeftFlag = false;
                speed1=30;
                speed2=50;
                forward(speed1, speed2);
                delay(500);
                speed1 = 35;
                speed2 = 30;              
                //forward(speed1, speed2);              
            } 
            else if (turnRightFlag)
            {
                turnRightFlag = false;
                speed1=50;
                speed2=30;
                forward(speed1, speed2);
                delay(500);
                speed1 = 35;
                speed2 = 30;              
                //forward(speed1, speed2);              
            }
            else  */
            {
            
                // no turn just go forward.
                speed1=35;
                speed2=30;
                //forward(speed1, speed2);              
            }
        } 
        //else if (L1 == 0 & L2 == 0 & L3 == 1)
        else if (L1 == 0 & L3 == 1)     // this navigates thick lines better.
        {
            //left & center see white, right sees black
            //turn right
            dir=2;
            speed1=fast;
            speed2=slow;
            //forward(speed1, speed2);
        }
        else
        {
            if(dir == 1)
            {
                speed1=fast;
                speed2=slow;
                //forward(speed1, speed2);
            }
            else
            {
                speed1=slow;
                speed2=fast;
                //forward(speed1, speed2);
            }
        }

        forward(speed1, speed2);

    }   // end if goFlag
  }
}

void reverse(int speed1, int speed2)
{
analogWrite(In4, speed1);
analogWrite(In3, 0);
analogWrite(In2, speed2);
analogWrite(In1, 0);
return;
} 

void forward (int speed1, int speed2)
{
analogWrite(In4, 0);
analogWrite(In3, speed1);
analogWrite(In2, 0);
analogWrite(In1, speed2);
return;
}

void stopNow()
{
  analogWrite(In4, 0); 
  analogWrite(In3, 0); 
  analogWrite(In2, 0); 
  analogWrite(In1, 0);
  return;
}

/*
void SendMessage(String message)
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds = 1 second
  mySerial.println("AT+CMGS=\"8053900976\"\r"); // Replace x with mobile number
  delay(100); 
  mySerial.print("<Car_Controller_Message=");// The SMS text you want to send
  delay(100);
  mySerial.print(message);
  delay(100);
  mySerial.println(">");
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}

int processTxt (String buffer, int buffsize)
{
    Serial.println("In processTxt");
 
    int command = -1;
 
    //Serial.println(buffer);

    // Txt Format from Phone:  
    //
    // +CMT: "+18057270090","","16/03/15,23:57:58-28"
    // This is a multi-line txt message.  
    // Second line is here.
    // Txt ends on this line.
    //
    // NOTE: There is a blank line at the end.
    
    
    // Txt Format from email txt:
    //
    // +CMT: "1410100007","","16/03/16,00:01:34-28"
    //
    // FRM:middleschoolengineer1@gmail.com
    // MSG:Hello, From python!
    // This is a multi-line txt message.
    // 
    // NOTE:  There is a blank line at the end.

    String numberPreamble = "+CMT: \"";
    String message;
    String listenerPhonePrefix = "ListenerPhoneNumber=";

    // Get the phone number of the txt sender.
    //
    int senderNumBegin = buffer.indexOf(numberPreamble) + numberPreamble.length();   
    int senderNumEnd = buffer.indexOf("\",", senderNumBegin);
    String senderNumber = buffer.substring(senderNumBegin, senderNumEnd);
    Serial.print("Phone Number: ");  
    Serial.println(senderNumber);

    // Get the message itself
    //
    int messageBegin = buffer.indexOf("\n", senderNumEnd) + 1;
    message = buffer.substring(messageBegin, buffer.length() - 1);
    Serial.println("TXT Message: ");
    Serial.println(message);

    String stopMessage = "STOP";
    String goMessage = "GO";
    String leftMessage = "LEFT";
    String rightMessage = "RIGHT";
    String statusMessage = "STATUS";

    if (buffer.indexOf(goMessage) > 0)
    {
        Serial.println("Message is Go!");  
        // send emergency stop signal here.
        command = 1;
    } 
    else if (buffer.indexOf(stopMessage) > 0 )
    {
        Serial.println("Message is Stop!");  
        // send emergency stop signal here.
        command = 2;
    }  
    else if (buffer.indexOf(leftMessage) > 0 )
    {
        Serial.println("Message is Stop!");  
        // send emergency stop signal here.
        command = 3;
    }    
    else if (buffer.indexOf(rightMessage) > 0 )
    {
        Serial.println("Message is Stop!");  
        // send emergency stop signal here.
        command = 4;
    }    
    else if (buffer.indexOf(statusMessage) > 0)
    {
        command = 99;
    }   
    else
    {
        Serial.println("Message is unhandled!");
    }
     
    Serial.println("returning from processTxt");
    
    return (command);
}

*/

