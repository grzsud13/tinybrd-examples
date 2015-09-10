
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
} data;


void setup()
{
  data.id = 6;
    
  data.status = temperature_setup();

  byte address[5] = {3,4,5};
  Radio.begin(address,100);
}

//**************************************************************


void radioWrite(struct SensorData &data, byte retry = 0)
{
  byte addressRemote[3] = { 0, 0, 3};
  
  if (retry == 5) {
    //we have failed transmit..
    data.seq ++;
    return;
  }
  data.retry = retry;
  Radio.write(addressRemote,data);
  while(true) {
    switch(Radio.flush()){
      case RADIO_SENT:
        data.seq++;
        return;
      case RADIO_LOST:
        radioWrite(data,retry+1);
        return;
    }
  }
  
}


void loop()
{
  //get data
  if (data.status) {
    data.payload=0;
  } else {
    data.payload = temperature_read();
  }
  data.battery = batteryRead();
  
  //send data
  radioWrite(data);

  //go to sleep
  Radio.off();
  sleep(15000);
}

