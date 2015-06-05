#include <SPI85.h>
#include <Mirf.h>
#include <MirfHardwareSpi85Driver.h>

#define CE 7
#define CSN 3

//#define R_ADDR  "sensor"
void radio_setup()
{
  Mirf.cePin = CE;
  Mirf.csnPin = CSN;
  Mirf.spi = &MirfHardwareSpi85;
  Mirf.init();
  
  Mirf.payload = sizeof(struct SensorData);
//  Mirf.setRADDR((byte *)read_id());
  Mirf.config();
}

void radio_write(struct SensorData data)
{
  Mirf.setTADDR((byte *)"SERV0");
  Mirf.send((byte *) &data);
  while (Mirf.isSending());
}

void radio_on() {
//  Mirf.powerUpTx();
  Mirf.powerUpRx();
}
void radio_off()
{
  Mirf.powerDown();
}

