
 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
const int trigPin = 7;
const int echoPin = 8;
// defines variables
long duration;
int distance;

void setup()
{
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   Serial.begin(9600); // Starts the serial communication
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
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
Serial.print("Distance:");
Serial.println(distance);
delay(500);
  
 if (distance < 15 && distance >= 10)
 {
  Serial.println("Distance Reached");
  SendMessage();  
 }
 else if (distance >10)
 {
  Serial.println("Send a command");
  ReceiveMessage();

  if (mySerial.available()>0)
  Serial.write(mySerial.read());

 }

 




   
}

void SendMessage()
  {
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+918369925301\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Technolab creation");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      
  }

 void ReceiveMessage()
  {
     mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      
  }
