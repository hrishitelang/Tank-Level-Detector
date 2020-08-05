int motorPlus = 5;
int motorMinus = 6;
void setup() {
  // put your setup code here, to run once:
pinMode(motorPlus,OUTPUT);
pinMode(motorMinus,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Anticlockwise
 
digitalWrite(motorPlus,HIGH);
digitalWrite(motorMinus,LOW);
delay(2000);
//Idle
digitalWrite(motorPlus,LOW);
digitalWrite(motorMinus,LOW);
delay(2000);
//clockwise
digitalWrite(motorPlus,LOW);
digitalWrite(motorMinus,HIGH);
delay(4000);
}
