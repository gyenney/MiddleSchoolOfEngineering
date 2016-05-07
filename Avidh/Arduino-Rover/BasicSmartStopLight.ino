double SmartButton = 8;
double DumbButton = 9;
boolean CanCarCross = false;

void setup() {
  Serial.begin(9600);
  pinMode(SmartButton, INPUT);
  pinMode(DumbButton, INPUT);
}

void loop() {
  String request = processRequest();
  if (request != "null"){
    Serial.println(request);
  }
  delay(100);
}

boolean smartcar(){
  return digitalRead(SmartButton);
  //For now, these methods are just tied to buttons,
  //later this is where we will put the logic to 
  //determine if the car is approaching the stoplight
}

boolean dumbcar(){
  return digitalRead(DumbButton);
  //For now, these methods are just tied to buttons,
  //later this is where we will put the logic to 
  //determine if the car is approaching the stoplight
}


String processRequest(){
  String label = Serial.readStringUntil(':'); //this is the label "request", made for readability. The code doesn't care about it, so this segment of the string is thrown out
  Serial.read(); //the next charecter will be a colon, and we want to get rid of that to so we can pass over it with this
  String request = Serial.readString(); //gets the rest of the string, what we care about
  boolean dumb = dumbcar();
  boolean smart = smartcar();

  if (request == " Go Straight" && smart && !dumb){
    return "Request Granted";
  }
  else /*if (request == " Go Straight")*/{
    return "Denied";
  }
//  else{
//    return "null";
//  }
}

