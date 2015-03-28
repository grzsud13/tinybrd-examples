struct SensorData
{
  float temperature;
  long battery;
};

void setup()
{
  radio_setup();
  temperature_setup();
  power_setup();

}
void loop()
{
  SensorData data;

  data.temperature = 0; //temperature_read();
  data.battery = battery_read();
  
  radio_write(data);
  
  power_down();
  power_up();
} 

