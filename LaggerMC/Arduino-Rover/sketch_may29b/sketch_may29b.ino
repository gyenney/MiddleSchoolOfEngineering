const int In1 = 3;      // In1
const int In2 = 5;      // In2
const int In3 = 6;     // In3
const int In4 = 11;     // In4

void setup() {
  // put your setup code here, to run once:
 // initialize the pins
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT); 

}

void loop() {
  // put your main code here, to run repeatedly:
forward(40, 35);
}
void forward (int speed1, int speed2)
{
analogWrite(In4, 0);
analogWrite(In3, speed1);
analogWrite(In2, 0);
analogWrite(In1, speed2);
return;
}
