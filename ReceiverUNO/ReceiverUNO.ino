#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

struct SensorData
  {
  byte id;
  long battery;
  byte status;
  float payload;
};

 
void setup()
{
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.payload = sizeof(SensorData);
  Mirf.setRADDR((byte *)"00001");
  
  Mirf.config();
  
  while (!Serial);
  Serial.begin(9600);
  Serial.println(F("START"));
}
 

void loop()
{
  if (Mirf.dataReady())
  {
    SensorData msg;
    Mirf.getData((byte *) &msg);
    Serial.print((byte)msg.id);
    Serial.print(F(","));
    Serial.print(msg.status);
    Serial.print(F(","));
    Serial.print(msg.battery);
    Serial.print(F(","));
    Serial.println(msg.payload);

  }
 // delay(1000);
 // Serial.println("TICK");
} 
