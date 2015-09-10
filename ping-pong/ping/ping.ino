#include <SPI.h>
#include <Radio.h>

#define LED   2
#define BUTTON  1


void lightOn(unsigned tme = 1000) {
  digitalWrite(LED, LOW);
  delay(tme);
  digitalWrite(LED, HIGH);
  delay(tme);

}


void setup() {
  pinMode(LED, OUTPUT);   
  digitalWrite(LED, HIGH);
  pinMode(BUTTON, INPUT_PULLUP);

    byte address[3] = {0, 0, 1};
    Radio.begin(address, 100);

  for (byte i = 0; i < 5; i++) {
    lightOn(100);
  }
  
}

byte pongAddr[3] = {1, 0, 0};
byte payload = 66;
byte received;

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON) == LOW) {
    Radio.write(pongAddr, payload);
    Radio.flush();
    delay(50);
  }
  if (Radio.available()) {
    received = 0;
    Radio.read(&received);
    if (received == 99) {
      lightOn();
    }

  }

}
