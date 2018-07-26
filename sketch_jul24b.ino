#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
SoftwareSerial gsmSerial(7, 8);

int FlexValue;
int pos =0;
int i;
void setup() {
    gsmSerial.begin(9600);
    Serial.begin(9600);    // the GPRS baud rate 
  myservo.attach(9);
  
  gsmSerial.println("AT");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CPIN?");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CREG?");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CGATT?");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIPSHUT");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIPSTATUS");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIPMUX=0");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CSTT=\"internet\"");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIICR");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIFSR");
  delay(1000);
  ShowSerialData();
  gsmSerial.println("AT+CIPSPRT=0");
  delay(1000);
  ShowSerialData();
  
  
  while(gsmSerial.available()!=0)
    {
      Serial.write(gsmSerial.read());
    }
  /*for(i=175;i<=395;i++)
  {
    pos=map(i,175,395,0,180);
    myservo.write(pos);
    Serial.println(i);
  }*/
  // put your setup code here, to run once:

}
void ShowSerialData()
{
  while(gsmSerial.available()!=0)
    Serial.write(gsmSerial.read());
}

void loop() {
 /* FlexValue=analogRead(A0);
      pos=map(FlexValue,175,395,0,180);
      */myservo.write(pos);
      //Serial.println(FlexValue);
  
  gsmSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(2000);
  ShowSerialData();

  gsmSerial.println("AT+CIPSEND");//begin send data to remote server
  delay(1000);
  ShowSerialData();
  String str="GET http://api.thingspeak.com/update?api_key=HU5JO83X8HSTV5D8&field1=" + String(pos);
  gsmSerial.println(str);//begin send data to remote server
  delay(2000);
  ShowSerialData();
      
      if(Serial.available())
      gsmSerial.write(Serial.read());
      if(gsmSerial.available())
    Serial.write(gsmSerial.read());
   
  // put your main code here, to run repeatedly:

}
