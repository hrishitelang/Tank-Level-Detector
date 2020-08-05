#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
#include <Servo.h>             //Servo library
 
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    
 

// defines pins numbers
const int trigPin = 7;
const int echoPin = 8;
char c;
// defines variables
long duration;
int distance;


void setup()

{
   servo_test.attach(11); 
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
Serial.print("Distance:");
Serial.println(distance);
delay(2000);


  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
    
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+918369925301\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Technolab creation");// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      break;



      
    case 'r':
      mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      delay(1000);
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());

}

/*
 void TapOn()

{
  for(angle = 0; angle < 360; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    servo_test.write(angle);                 //command to rotate the servo to the specified angle
                           
  } 

}

void TapOff()
{
     for(angle = 360; angle>=0; angle-=1)     // command to move from 180 degrees to 0 degrees 
  {                                
    servo_test.write(angle);              //command to rotate the servo to the specified angle
                          
  } 
}




 
    c = mySerial.read();
    Serial.println(c);
    if (c == 'A')
    {
      TapOff();
    }
    else if (c == 'B')
    {
      TapOff();
    }
 */   
    
