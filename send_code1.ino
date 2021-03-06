#include <SPI.h>  
#include "RF24.h"
#include <nRF24L01.h>

#include "EmonLib.h"
EnergyMonitor emon1;

RF24 myRadio (7,8);
const byte address = "00005";

struct package
{
  //int id=100;
  float current_value ;
  char  text[100] = "Text to be transmitted";
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(111);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openWritingPipe(address);
  myRadio.stopListening();
  delay(1000);
  emon1.current(A0, 111.1); // (pinout,calibration)
  //pinMode(A0,INPUT);
}

void loop(){
     
 

  myRadio.write(&data, sizeof(data));

  Serial.print("\nPackage:");
  //Serial.print(data.id);
 data.current_value = emon1.calcIrms(1480);  // Calculate Irms only. Irms = Current Root Mean Square value = Measured current
 
  //Serial.print(current_value*230.0);         // Apparent power.
  //Serial.print(" ");                   // Apparent power is Irms * Vrms (Voltage Root Mean Square value, which is 230 for Arduinos)
  //Serial.println(current_value);
//  Serial.print("\n");
  Serial.println(data.current_value/10.25);
  Serial.println(data.text);
//  data.id = current_value+1;
//  data.temperature = data.temperature+0.1;
  delay(4000);

}
