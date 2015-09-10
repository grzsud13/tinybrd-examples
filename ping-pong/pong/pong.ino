#include <SPI.h>
#include <Radio.h>

#define LED   1

void lightOn(unsigned tme = 1000) {
  digitalWrite(LED, LOW);
  delay(tme);
  digitalWrite(LED, HIGH);
  delay(tme);

}
void setup() {
  // put your setup code here, to run once:
  byte address[3] = {1, 0, 0};
  Radio.begin(address, 100);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  for (byte i = 0; i < 5; i++) {
    lightOn(100);
  }

}
byte pingAddr[3] = { 0, 0, 1 };
byte payload;

void loop() {
  // put your main code here, to run repeatedly:
  if (Radio.available()) {
    lightOn(100);
    Radio.read(&payload);
    if (payload == 66) {
      payload = 99;
      Radio.write(pingAddr, payload);
      Radio.flush();
      lightOn(400);
    }
  }
}
