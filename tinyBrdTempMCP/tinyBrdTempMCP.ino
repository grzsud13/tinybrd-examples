
#include <SPI.h>
#include <Radio.h>
#include <Battery.h>
#include <PinChangeInterrupt.h>

volatile boolean sendData = false;

void irq() {
  sendData = true;
}


struct SensorData
{
  byte id;
  float payload;
} data;


void setup()
{
  data.id = 1;
  pinMode(1, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  analogReference(INTERNAL);
  byte address[5] = {3, 4, 5};
  Radio.begin(address, 100);
  attachPcInterrupt(1, irq, FALLING);
}

//**************************************************************


void radioWrite(struct SensorData &data, byte retry = 0)
{
  byte addressRemote[3] = {99, 0, 3};

  if (retry == 5) {
    //we have failed transmit..
    return;
  }
  Radio.write(addressRemote, data);
  while (true) {
    switch (Radio.flush()) {
      case RADIO_SENT:
        return;
      case RADIO_LOST:
        radioWrite(data, retry + 1);
        return;
    }
  }

}

#define SENSOR_PIN A1

float temperatureRead() {
  float temp = analogRead(SENSOR_PIN) * 1.1 / 1024.0 - 0.5;
  temp = temp / 0.01;
  return temp;
}

void loop()
{
  if (sendData) {
    sendData = false;
    data.payload = temperatureRead();
    radioWrite(data);
    Radio.off();
//    delay(30);
  }

  //go to sleep
  sleep(5000);
  digitalWrite(10,HIGH);
  delay(200);
  digitalWrite(10,LOW);
}

