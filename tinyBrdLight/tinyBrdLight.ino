
#define LED 1

struct SensorData
  {
  byte id;
  long battery;
  byte status;
  float payload;
};

SensorData data;
 


void setup()
{
  data.status = 0;
  radio_setup();
  light_setup();
  power_setup();
  
  pinMode(LED,OUTPUT);

}

void loop()
{
  //get data
  data.payload = (float)light_read();
  data.battery = battery_read();
  data.id = 100;


  //send data
  radio_write(data);

  //go to sleep and go back
  power_down();
  power_up();
  
}

