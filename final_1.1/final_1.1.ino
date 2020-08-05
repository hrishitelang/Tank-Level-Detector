#include <SoftwareSerial.h>
#include <Servo.h> 
SoftwareSerial mySerial(9, 10); 
Servo servo_test;        //initialize a servo object for the connected servo  
                
int angle = 0;    
 

// defines pins numbers
const int trigPin = 7;
const int echoPin = 8;
String buffer1;
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
   delay(900);


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

delay(500);


//buffer1=mySerial.read();
//buffer1.remove(0,46); //Removes first 23 characters
//Serial.println(buffer1);

if (distance < 8)

  {
    Serial.print("Distance:");
    Serial.println(distance);
    SendMessageOFF();
    Serial.println("Distance Reached!");
    delay(100);
    //ReceiveMessage();
    //delay(1000);
    TapOff();
    delay(100);
    
  }
else if (distance > 20 && distance < 30)
{
  Serial.print("Distance:");
  Serial.println(distance);
  Serial.println("Tap is turning on");
  SendMessageON();
  delay(100);
  TapOn();
  delay(100);
}

 if (mySerial.available()>0)
 
   Serial.write(mySerial.read());
 
}

 void SendMessageOFF()

{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919004790838\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("Your tank is nealy full and the tap is turned off");// The SMS text you want to send

  delay(1000);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}

 void SendMessageON()

{

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919004790838\"\r"); // Replace x with mobile number

  delay(1000);

  mySerial.println("Your tap is turned on");// The SMS text you want to send

  delay(1000);

  mySerial.println((char)26);// ASCII code of CTRL+Z

  delay(1000);

}

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


  void DialCall()

 {

  mySerial.println("ATD+919004790838;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);

 }

/* void ReceiveMessage()

{

    mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMs 
    delay(1000);

   //Serial.println(buffer1);
  // String buffer1.remove(0,46);
   //Serial.println(buffer1);

   if (mySerial.available()>0)
   {
    TapOff();
   }
    if (buffer1 == 'A')
    {
      TapOff();
    }
    else if (buffer1 == 'B')
    {
      TapOn();
    }*/
    
    
