#include <SPI.h>
#include <Radio.h>

TinyDebugSerial debug = TinyDebugSerial();

#define MAC 2

byte leds[4] = { 1, 2, 8, 9};
byte serverAddr[3] = { 0, 0, 3 };
byte address[3] = { MAC, 0, 0 };

struct Payload
{
  byte id;
  unsigned int payload;
} data;

void setup() {
  // put your setup code here, to run once:
  debug.begin(9600);
  debug.println(F("START"));
  Radio.begin(address, 100);

  data.id = MAC;
  for (byte i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

int i = 0;

void write_data(Payload data, byte cnt = 0) {
  Radio.write(serverAddr, data);
  debug.print(F("Sent to: "));
  for (byte i = 0; i < 3; i++) {
    debug.print(serverAddr[i], DEC);
    debug.print(F(","));
  }
  debug.println(F(""));
  //          delay(20);
  if (RADIO_LOST == Radio.flush(RADIO_BLOCK)) {
    debug.println(F("NOT SENT"));
    if (cnt > 7) {
      return;
    }
    delay(random(15));
    write_data(data, cnt + 1);
    return;
  } else {
    debug.println(F("Waits/sent?"));
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  if (byte cnt = Radio.available()) {
    if (cnt) {
      byte cmd[cnt];
      Radio.read(cmd);
      debug.print(F("C: "));
      debug.print(cnt, DEC);
      debug.print(F(", "));
      debug.println(cmd[0], DEC);

      switch (cmd[0]) {
        case 102:
          debug.print(F("Set led to: "));
          debug.println(cmd[1], DEC);
          for (byte i = 0; i < 4; i++) {
            digitalWrite(leds[i], i >= cmd[1]);
          }
          break;
        case 99:
          int ret = map(analogRead(A0), 0, 1023, 0, 4);
          debug.println(ret, DEC);
          data.payload = ret;
          write_data(data);
          break;
      }

    }
  }
  i++;
  if (i > 100) {
    debug.println(F("TICK"));
    i = 0;
  }
  delay(10);
}
