
#define NO_TEMP_SENSOR   1
#define LED 1

struct SensorData
  {
  byte id;
  long battery;
  byte status;
  float payload;
};


SensorData data;
 
void pulse(byte led, unsigned int time=1000, byte cnt = 1) {
  for (byte i=0;i++;i<cnt) {
    digitalWrite(led,HIGH);
    delay(time/2);
    digitalWrite(led,LOW);
    delay(time/2);
  }
}


void setup()
{
  data.status = 0;
  radio_setup();
  if (temperature_find_sensor() == -1)
    data.status = NO_TEMP_SENSOR;
  temperature_setup();
  power_setup();
  pinMode(LED,OUTPUT);

  if (!data.status){
    pulse(LED,500,20);
  }
}

void loop()
{
  //get data
  data.payload = temperature_read();
  data.battery = battery_read();
  data.id = 3;

  //send data
  radio_write(data);

  //go to sleep and go back
  power_down();
  power_up();
  
}

