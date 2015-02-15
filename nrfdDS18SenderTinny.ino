
#include <OneWire.h>
#include <DS18B20.h>

struct SensorData
{
  float temperature;
  long battery;
};
 

#define ONEWIRE_PIN 0

byte address[8] = {0x28, 0xE6, 0x3C, 0xCC, 0x5, 0x0, 0x0, 0x3E};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensor(&onewire);

void setup()
{
  radio_setup();
  sensor.begin();
  sensor.request(address);
  
  power_setup();

}
void loop()
{
//  delay(100);

if (sensor.available())
  {

    SensorData tmp;
    tmp.temperature = sensor.readTemperature(address);
    tmp.battery = battery_read();
    radio_write(tmp);
    sensor.request(address);
//    delay(100);
  }

  power_down();
  power_up();
} 

