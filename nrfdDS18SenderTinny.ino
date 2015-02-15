#include <avr/sleep.h> //Needed for sleep_mode
#include <avr/wdt.h> //Needed to enable/disable watch dog timer

#include <SPI85.h>
#include <Mirf.h>
#include <MirfHardwareSpi85Driver.h>

#include <OneWire.h>
#include <DS18B20.h>

#define CE 7
#define CSN 3
#define LED  1

#define ONEWIRE_PIN 0

byte address[8] = {0x28, 0xE6, 0x3C, 0xCC, 0x5, 0x0, 0x0, 0x3E};

OneWire onewire(ONEWIRE_PIN);
DS18B20 sensor(&onewire);



ISR(WDT_vect) {
//Don't do anything. This is just here so that we wake up.
}


void setup()
{
  Mirf.cePin = CE;
  Mirf.csnPin = CSN;
  Mirf.spi = &MirfHardwareSpi85;
  Mirf.init();
  
  Mirf.payload = sizeof(float);
   
  Mirf.config();
  
  sensor.begin();
  sensor.request(address);
  
   set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
sleep_enable();
}
 //Sets the watchdog timer to wake us up, but not reset
//0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
//6=1sec, 7=2sec, 8=4sec, 9=8sec
//From: http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/
void setup_watchdog(int timerPrescaler) {
if (timerPrescaler > 9 ) timerPrescaler = 9; //Limit incoming amount to legal settings
byte bb = timerPrescaler & 7;
if (timerPrescaler > 7) bb |= (1<<5); //Set the special 5th bit if necessary
//This order of commands is important and cannot be combined
MCUSR &= ~(1<<WDRF); //Clear the watch dog reset
WDTCSR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
WDTCSR = bb; //Set new watchdog timeout value
WDTCSR |= _BV(WDIE); //Set the interrupt enable, this will keep unit from resetting after each int
}

 
 void pulseLED(){
  digitalWrite(LED, HIGH);
  delay(250);
  digitalWrite(LED, LOW);  
  delay(250);
}

float heartbeat = 64;
void loop()
{
  

if (sensor.available())
  {

    float temperature = sensor.readTemperature(address);
    Mirf.setTADDR((byte *)"SERV0");
    Mirf.send((byte *) &temperature);
    while (Mirf.isSending());
    sensor.request(address);
    //pulseLED();
  }
//  delay(300);

    ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
    digitalWrite(CE, LOW);
    for (byte i=0; i<4; i++) {
      setup_watchdog(4); //Setup watchdog to go off after 8sec
      sleep_mode(); //Go to sleep! Wake up 1sec later and check water
    }  
      
    ADCSRA |= (1<<ADEN); //Enable ADC
   digitalWrite(CE, HIGH);
   
/*
Mirf.setTADDR((byte *)"SERV0");
  Mirf.send((byte *) &heartbeat);
    while (Mirf.isSending());
//  pulseLED();
*/
} 

