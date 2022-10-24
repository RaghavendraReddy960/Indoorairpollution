
#include <Wire.h>
#include "processdata.h"
#include <SPI.h>
#include "Adafruit_Sensor.h"

#define RXD2 16
#define TXD2 17

float h = 70.80;
void setup(){
   Serial.begin(115200);
   Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Pm25 = 0;
  Pm10 = 0;
  
  }
void loop(){
   turnon();
  delay(2000);
  

  ProcessSerialData();
  



 Pm25 = Pm25 / (1.0 + 0.48756 * pow((h / 100.0), 8.60068));
 Pm10 = Pm10 / (1.0 + 0.81559 * pow((h / 100.0), 5.83411));
  Serial.println();
  Serial.print("Pm2.5 ");
  Serial.print(Pm25);
  Serial.println();//  Display();
  Serial.print("Pm10 ");
  Serial.print(float(Pm10) / 10.0);
  Serial.println();
   turnoff();
}

void turnoff() {
Serial2.flush();
for (uint8_t j = 0; j < 19; j++) Serial2.write(SLEEPCMD[j]);
}

void turnon() {
  Serial2.write(0x01);
}
