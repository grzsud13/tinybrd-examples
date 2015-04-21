

struct SensorData
{
  float temperature;
  byte humidity;
  long battery;
  char id;
};





void setup()
{
  radio_setup();
//  temperature_setup();
  dht_setup();
  power_setup();

}
void loop()
{
  SensorData data;

  data.temperature = dht_temp();
  data.humidity = humidity_read();
  data.battery = battery_read();
  data.id = read_id()[0];
  radio_write(data);

  power_down();
  power_up();
}

