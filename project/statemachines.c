#include <msp430.h>
#include "statemachines.h"
#include "led.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

char up; /* used to see if the siren is increasing */

void siren_on()/* activate the siren */
{
  double x;
  short cycles = 0;
  if(up) x += 225; /* x is 225 Hz  */
  else x += 450; /* x is 450 Hz*/
  
  x = (x / 1000) * 500;/* Converting x to kHz then into cycles */
  cycles += x;
  buzzer_set_period(cycles);
}

void light_advance() /* just turns on the green LED */
{
  buzzer_set_period(0);
  green_on = 1;
  led_update();
}

void buzz_off()/* Turns off everything */
{
  buzzer_set_period(0);
  green_on = 0;
  led_update();
}
