
#include <SPI.h>
#include <Radio.h>
#include <Battery.h>


struct SensorData
  {
  byte id;
  long battery;
  byte status;
  float payload;
  byte seq;
  byte retry;
};
SensorData data;

byte addressRemote[5] = { 0, 0, 3};

void setup()
{
  data.status = 0;
  data.id = 100;

  byte address[5] = {3, 4, 5};
  Radio.begin(address, 100);

}

//**************************************************************


void radio_write(struct SensorData &data, byte retry = 0)
{
  if (retry == 5) {
    //we have failed transmit..
    data.seq ++;
    return;
  }
  data.retry = retry;
  Radio.write(addressRemote, data);
  while (true) {
    switch (Radio.flush()) {
      case RADIO_SENT:
        data.seq++;
        return;
      case RADIO_LOST:
        radio_write(data, retry + 1);
        return;
    }
  }

}


void loop()
{
  //get data
  data.payload = (float)light_read();
  data.battery = batteryRead();

  //send data
  radio_write(data);

  //go to sleep
  Radio.off();
  sleep(10000);
  //  wakeUp();
}


