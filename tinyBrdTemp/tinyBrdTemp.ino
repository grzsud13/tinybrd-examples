#include <SPI.h>
#include <Radio.h>
#include <Battery.h>

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
  pinMode(LED,OUTPUT);
  data.id = 3;
  if (data.status != 0){
    pulse(LED,500,20);
  }
}

void loop()
{
  //get data
  data.payload = temperature_read();
  data.battery = batteryRead();
  

  //send data
  radio_write(data);

  //go to sleep
  Radio.off();
  for (byte i=0;i<4; i++){
    sleep(SLEEP_8S);
  };
  wakeUp();
}

