#include <OneWire.h>

#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>


// Numer pinu cyfrowego do którego podłaczyłęś czujniki
const byte ONEWIRE_PIN = 4;

OneWire onewire(ONEWIRE_PIN);

 
void setup()
{
  Mirf.cePin = 7;
  Mirf.csnPin = 8;
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  Mirf.payload = sizeof(float);
  Mirf.setRADDR((byte *)"SERV0");
  
  Mirf.config();
  
  while (!Serial);
  Serial.begin(9600);
  Serial.println("START");
}
 
void readDSAddress() {
  byte address[8];
  
  onewire.reset_search();
  while(onewire.search(address))
  {
    if (address[0] != 0x28)
      continue;
      
    if (OneWire::crc8(address, 7) != address[7])
    {
      Serial.println(F("Błędny adres, sprawdz polaczenia"));
      break;
    }
    
    for (byte i=0; i<8; i++)
    {
      Serial.print(F("0x"));
      Serial.print(address[i], HEX);
      
      if (i < 7)  
        Serial.print(F(", "));
    }
    Serial.println();
  }
  
  while(1);
}

void loop()
{
//  readDSAddress();
  if (Mirf.dataReady())
  {
    float temperature;
    Serial.println("mam!");
    Mirf.getData((byte *) &temperature);
    Serial.println(temperature);
  }
 // delay(1000);
 // Serial.println("TICK");
} 
