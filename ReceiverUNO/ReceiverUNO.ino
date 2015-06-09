#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

struct SensorData
{
  float temperature;
  long battery;
  byte id;
  byte status;
};

 
void setup()
{
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.payload = sizeof(SensorData);
  Mirf.setRADDR((byte *)"00002");
  
  Mirf.config();
  
  while (!Serial);
  Serial.begin(9600);
  Serial.println(F("START"));
}
 

void loop()
{
  if (Mirf.dataReady())
  {
    SensorData payload;
    Mirf.getData((byte *) &payload);
    Serial.print((byte)payload.id);
    Serial.print(F(","));
    Serial.print(payload.status);
    Serial.print(F(","));
    Serial.print(payload.battery);
    Serial.print(F(","));
    Serial.println(payload.temperature);

  }
 // delay(1000);
 // Serial.println("TICK");
} 
