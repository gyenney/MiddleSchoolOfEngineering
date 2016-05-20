// based on AdvancedLineFollowing.ino
// from StemCenterUSA.com
#include <SoftwareSerial.h> 

const int myRx = 7;  // Shield: Rx=7, Tx=8
const int myTx = 8;  // Board:  Rx=4, Tx=2


char inputBuffer[256];
int commandValue;


SoftwareSerial mySerial(myRx, myTx);

const int Line1 = 10;     // Left Line Sensor
const int Line2 = 12;     // Center Line Sensor
const int Line3 = 13;    // Right Sensor 

const int In1 = 3;      // In1  
const int In2 = 5;      // In2
const int In3 = 6;      // In3
const int In4 = 11;     // In4
const int batPin = A0;

#define num 6

void setup() 
{
  // initialize the pins
  pinMode(myRx, INPUT_PULLUP);
  pinMode(myTx, OUTPUT);

  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT); 
  pinMode(Line1, INPUT); 
  pinMode(Line2, INPUT); 
  pinMode(Line3, INPUT); 
  
  Serial.begin(19200);
  mySerial.begin(19200);
  Serial.begin(19200);
 
  delay(100);
  mySerial.println("AT+IPR=19200");


  Serial.println ("Press \'s <enter>\' to Send a message and press \'r <enter>\' to receive a message.");
}

void loop()
{
  int rLED[num], cLED[num], lLED[num];
  int  lSum, cSum, rSum;
  int fast;
  int speed1;
  int speed2;
  float scale1, scale2, scale3;
  boolean debugPrint;
  int L1, L2, L3;
  int batVoltage;
  
  for(int i=0; i<num; i++)
  {
    rLED[i]=0;
    cLED[i]=1;
    lLED[i]=0;
  }
  rSum = 0;
  cSum = 0;
  lSum = 0;
//************ Turn on debuging here ****************
  //debugPrint = true;
  debugPrint = false;
//***************************************************
  delay(100);
  forward(0, 0);
  while(1==1)
  {


    
      if (Serial.available() > 0)
  {
     switch(Serial.read())
     {
        case 's':
          Serial.println("Send Message.");
          SendMessage("Hello, from the SMS_car_controller!");
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
  
  Serial.print("Command is: ");
  Serial.println(commandValue);
  
  // take appropriate action based on the command that was returned.
 


    




  
    batVoltage = analogRead(batPin);
    L1 = digitalRead(Line1);
    L2 = digitalRead(Line2);
    L3 = digitalRead(Line3); 
    if ((L1 == 1) && (L2 == 1) && (L3 ==1))
    {
      speed1 = 0;
      speed2 = 0;
      forward(speed1, speed2);
      if(debugPrint)
      {
        Serial.println("In Lift Mode"); 
      }
    }
    else if ((L1 != 0) || (L2 != 0) || (L3 !=0))
    {
      rSum = 0;
      cSum = 0;
      lSum = 0;
      for(int i=0; i<num-1; i++)
      {
        rLED[i]=rLED[i+1];
        cLED[i]=cLED[i+1];
        lLED[i]=lLED[i+1];
      }
      
      rLED[num-1]=L1;
      cLED[num-1]=L2;
      lLED[num-1]=L3;
      
      for(int i=0; i<num; i++)
      {
        rSum = rSum + rLED[i] * (8-i);
        cSum = cSum + cLED[i] * (8-i);
        lSum = lSum + lLED[i] * (8-i);
      }
      
      if(debugPrint)
      {
        Serial.println(""); 
        Serial.print(L1);
        Serial.print(", ");
        Serial.print(L2);
        Serial.print(", ");
        Serial.println(L3); 
        Serial.print(rSum);
        Serial.print(", ");
        Serial.print(cSum);
        Serial.print(", ");
        Serial.println(lSum);  
      }
        scale1= (float) rSum + (float) cSum;
        scale2= (float) lSum + (float) cSum;
        scale3= (float) lSum + cSum + rSum;

         fast= 80000. / (float) batVoltage;
         
         if(rSum > lSum)
         {
           speed1 = fast;
           speed2 = scale2/scale1 * fast;
         }
         else
         {
           speed2 = fast;
           speed1 = scale1/scale2 * fast;
         }
         
         forward(speed1, speed2);
      
        if(debugPrint)
        {
          Serial.print(scale1);
          Serial.print(", "); 
          Serial.println(scale2);
          Serial.print(speed1);
          Serial.print(", "); 
          Serial.println(speed2);
          Serial.print("battery Voltage = ");
          Serial.println(batVoltage);
          Serial.print("fast = ");
          Serial.println(speed2);
          delay(500);
        }
    }
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

void SendMessage(String message)
{
  Serial.println("SendMessage()");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds = 1 second
  mySerial.println("AT+CMGS=\"phone_number_goes_here\"\r"); // Replace x with mobile number
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

    if (buffer.indexOf(goMessage) > 0)
    {
        Serial.println("Message is Go!");  
        // send emergency stop signal here.
        command = 1;
    } else if (buffer.indexOf(stopMessage) > 0 )
    {
        Serial.println("Message is Stop!");  
        // send emergency stop signal here.
        command = 2;
    }
    else
    {
        Serial.println("Message is unhandled!");
    }
     
    Serial.println("returning from processTxt");
    
    return (command);
}


