#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

// defines pins numbers
const int trigPin = 7;
const int echoPin = 8;
int motorPlus = 5;
int motorMinus = 6;
// defines variables
long duration;
int distance;

void setup()

{
   pinMode(motorPlus,OUTPUT);
   pinMode(motorMinus,OUTPUT);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   Serial.begin(9600); // Starts the serial communication
   mySerial.begin(9600);   // Setting the baud rate of GSM Module 
   Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
   delay(100);
}

void loop()
{

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);

if (distance < 15 && distance >= 10)
  {
    SendMessage();
    Serial.println("Distance Reached!");
    delay(1000);
  }
else if (distance < 10)
  {
    DialCall();
    Serial.println("Danger Point Reached!");
    delay(2000);
    char inChar = Serial.read();
    //anticlockwise
      if (inChar == 1)    //ON
    {
      digitalWrite(motorPlus,HIGH);
      digitalWrite(motorMinus,LOW);
      delay(2000);
    }
    //clockwise
       if(inChar == 0)  //OFF
    {
      digitalWrite(motorPlus,LOW);
      digitalWrite(motorMinus,HIGH);
      delay(4000);
    }
 
  {

    if (Serial.available()>0)
    switch(Serial.read())
  {

    case 's':

      SendMessage();

      break;

    case 'd':

      DialCall();

      break;

    case 'r':
      
      ReceiveMessage();
 
      break;

  }

 if (mySerial.available()>0)

   Serial.write(mySerial.read());

}
}

 void SendMessage()


{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919004790838\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("Your Water is overflowing! Please type 1 to switch on the tap and 0 to switch off.");// The SMS text you want to send

  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}

 void ReceiveMessage()

{

      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      
      delay(1000);

}


  void DialCall()

 {

  mySerial.println("ATD+919004790838;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);

 }
