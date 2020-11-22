#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

static char up; /* used to see if the siren is increasing */

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

void buzz_off()/* Turns off everything */
{
  buzzer_set_period(0);
  red_on = 0;
  green_on = 0;
  led_update();
}

void light_advance() /* just turns on both LEDs */
{
  buzzer_set_period(0);
  red_on = 1;
  green_on = 1;
  led_update();
}

void blink_advance()/* siren advance w/out the buzzer */
{
  static char state = 0;
  buzzer_set_period(0);
  switch(state)
    {
    case 0:/* state 1 green on, red off */ 
      green_on = 1;
      red_on = 0;
      led_update();
      state++;
      break;
    case 1:/* state 2 red on, green off*/
      red_on = 1;
      green_on = 0;
      led_update();
      state = 0;
    default:
      break;
    }
}

void siren_advance()/* alternate between toggling red & green */
{
  static char state = 0;
  switch(state)
    {
    case 0:/* state 1 green on, red off */ 
      green_on = 1;
      red_on = 0;
      up = 1;
      led_update();
      state++;
      break;
    case 1:/* state 2 red on, green off*/
      red_on = 1;
      green_on = 0;
      up = 0;
      led_update();
      state = 0;
    default:
      break;
    }
}
