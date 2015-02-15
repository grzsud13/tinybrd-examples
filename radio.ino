#include <SPI85.h>
#include <Mirf.h>
#include <MirfHardwareSpi85Driver.h>

#define CE 7
#define CSN 3

void radio_setup()
{
  Mirf.cePin = CE;
  Mirf.csnPin = CSN;
  Mirf.spi = &MirfHardwareSpi85;
  Mirf.init();
  
  Mirf.payload = sizeof(struct SensorData);
   
  Mirf.config();
}

void radio_write(struct SensorData data)
{
  Mirf.setTADDR((byte *)"SERV0");
  Mirf.send((byte *) &data);
  while (Mirf.isSending());
}

void radio_off()
{
  Mirf.powerDown();
}

