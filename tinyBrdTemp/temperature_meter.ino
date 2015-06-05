#include <OneWire.h>
#include <DS18B20.h>

#define ONEWIRE_PIN 0

byte address[8] = {0x28, 0xE6, 0x3C, 0xCC, 0x5, 0x0, 0x0, 0x3E};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensor(&onewire);

void temperature_setup(){
  sensor.begin();
  sensor.request(address);
};

float temperature_read(){
  sensor.request(address);
  while (!sensor.available());
  float temperature = sensor.readTemperature(address);
  
  return temperature;

}

