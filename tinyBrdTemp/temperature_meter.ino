#include <OneWire.h>

#include <DS18B20.h>

#define ONEWIRE_PIN 0


#define NO_TEMP_SENSOR   1


byte address[8] = {0x28, 0xE6, 0x3C, 0xCC, 0x5, 0x0, 0x0, 0x3E};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensor(&onewire);

int temperature_setup(){
  if (temperature_find_sensor() == -1)
    return NO_TEMP_SENSOR ;

  sensor.begin();
  sensor.request(address);
};

int  temperature_find_sensor() {

  onewire.reset_search();
  while(onewire.search(address))
  {
    if (address[0] != 0x28)
      continue;

    if (OneWire::crc8(address, 7) != address[7])
    {
      return -1;
    }
    return 0;
  }
  return -1;
}


float temperature_read(){
  sensor.request(address);
  while (!sensor.available());
  float temperature = sensor.readTemperature(address);
  
  return temperature;

}

