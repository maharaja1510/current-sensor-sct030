#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7,8); //(CE,CSE)
const byte address = "00005"; // ADDRESS COMMUNICATE TO RECEIVE
//#define light1 3
struct package
{
  //int id=0;
  float current_value ;
  char  text[100] ="empty";
};





typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  myRadio.begin();
  myRadio.setChannel(117);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1  , address);
 // myRadio.openReadingPipe(4, addresses[0]);
  myRadio.startListening();
  //pinMode(light,OUTPUT);
}


void loop()  
{

  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
     
    }
    Serial.print("\nPackage:");
   // Serial.print(data.id);
//    Serial.print("\n");
Serial.println(data.current_value);
   // Serial.println(data.current_value);
    Serial.println(data.text);
//    if(data.id==1)
//    {
//      digitalWrite(light1,HIGH);
//delay(1000);
}
 
//else
   //  {
   // Serial.println("aaa");
   
  }
//  delay(1000);

// 
