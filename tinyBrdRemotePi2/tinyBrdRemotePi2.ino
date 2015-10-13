#include <SPI.h>
#include <Radio.h>

TinyDebugSerial debug = TinyDebugSerial();

byte leds[4] = { 1, 2, 8, 9};
byte serverAddr[3] = { 0, 0, 3 };
byte address[3] = { 3, 0, 0 };

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

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
  data.id = 1;
  for (byte i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

int i = 0;
unsigned int tick = 1;

void loop() {
  // put your main code here, to run repeatedly:
  if (byte cnt = Radio.available()) {
//      debug.print(F("C: "));
//      debug.print(cnt, DEC);
    if (cnt > 32) {
      debug.println(F("\n-------->> RESET <<------------"));
      Radio.begin(address, 100);
      cnt = 0;
    }
    if (cnt) {
      byte cmd[cnt];
      Radio.read(cmd);
//      debug.print(F(", "));
//      debug.println(cmd[0], DEC);

      switch (cmd[0]) {
        case 102:
//          debug.print(F("Set led to: "));
//          debug.println(cmd[1], DEC);
          for (byte i = 0; i < 4; i++) {
            digitalWrite(leds[i], i >= cmd[1]);
          }
          break;
        case 99:
          int ret = map(analogRead(A0), 0, 1023, 0, 4);
//          debug.println(ret, DEC);
          data.payload = ret;
          Radio.write(serverAddr, data);
          //          delay(20);
          if (RADIO_LOST == Radio.flush(RADIO_BLOCK)) {
//            debug.println(F("NOT SENT"));
          } else {
//            debug.println(F("Waits/sent?"));
          }
      }

    }
  }
  i++;
  if (i > 100) {
    debug.print(F("TICK "));
    debug.print(tick, DEC);
    debug.print(F(", "));
    debug.println(freeRam(), DEC);
    tick++;
    i = 0;
  }
  delay(10);
}
