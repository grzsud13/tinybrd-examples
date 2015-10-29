#include <SPI.h>
#include <Radio.h>

TinyDebugSerial debug = TinyDebugSerial();

byte leds[4] = { 1, 2, 8, 9};
byte serverAddr[3] = { 0, 0, 3 };
byte address[3] = { 3, 0, 0 };

struct Payload
{
  byte id;
  unsigned int payload;
} data;

void setup() {
  // put your setup code here, to run once:
  debug.begin(38400);
  debug.println(F("START"));
  Radio.begin(address, 100);

  data.id = 1;
  for (byte i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  debug.println(F("avail"));

  if (byte cnt = Radio.available()) {
    byte cmd[cnt];
    debug.println(F("read"));
    Radio.read(cmd);
    debug.println(F("done"));

    //      debug.print(F("C: "));
    //      debug.print(cnt, DEC);
    //      debug.print(F(", "));
    //      debug.println(cmd[0], DEC);

    switch (cmd[0]) {
      case 102:
        //        debug.print(F("Set led to: "));
        //        debug.println(cmd[1], DEC);
        for (byte j = 1; j <= 4; j++) {
          bool val = j <= cmd[1];
          digitalWrite(leds[j - 1], val);
          //          debug.print(j,DEC);
          //          if (val) { debug.println(F(": T")); } else { debug.println(F(": F"));}
        }
        break;
      case 99:
        int ret = analogRead(A0);
        //        debug.println(ret, DEC);
        data.payload = ret;
        debug.println(F("write"));
        Radio.write(serverAddr, data);
        //          delay(20);
        debug.println(F("flush"));
        if (RADIO_LOST == Radio.flush(RADIO_BLOCK)) {
          debug.println(F("NOT SENT"));
        } else {
          debug.println(F("Waits/sent?"));
        }


    }
  }
  i++;
  if (i > 500) {
    debug.print(F("TICK "));
    debug.println(millis(), DEC);
    i = 0;
  }
  delay(10);
}
