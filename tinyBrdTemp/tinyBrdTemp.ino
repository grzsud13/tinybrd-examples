
#define LED 1

struct SensorData
{
  float temperature;
  long battery;
  byte id;
  byte status;
};


SensorData data;
 


void setup()
{
  data.status = 0;
  radio_setup();
  data.status = temperature_setup();
  power_setup();
  
  pinMode(LED,OUTPUT);

  check_for_errors();
}

void loop()
{
  //get data
  data.temperature = 128;//temperature_read();
  data.battery = battery_read();
  data.id = 2;

  //send data
  radio_write(data);

  //go to sleep and go back
  power_down();
  power_up();
  
}

