#include <avr/sleep.h>
#include <avr/wdt.h>

ISR(WDT_vect) {
//Don't do anything. This is just here so that we wake up.
}

void power_setup()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
}

//Sets the watchdog timer to wake us up, but not reset
//0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
//6=1sec, 7=2sec, 8=4sec, 9=8sec
void setup_watchdog(int timerPrescaler)
{
  if (timerPrescaler > 9 )
    timerPrescaler = 9;
  
  byte bb = timerPrescaler & 7;
  if (timerPrescaler > 7) 
    bb |= (1<<5);
    
  MCUSR &= ~(1<<WDRF); //Clear the watch dog reset
  WDTCSR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
  WDTCSR = bb; //Set new watchdog timeout value
  WDTCSR |= _BV(WDIE); //Set the interrupt enable, this will keep unit from resetting after each int
}

void power_down()
{
   radio_off();
  
  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
  for (byte i=0; i<4; i++) {
      setup_watchdog(5); 
      sleep_mode();
  }
}

void power_up()
{
  radio_on();
  ADCSRA |= (1<<ADEN); //Enable ADC
}
