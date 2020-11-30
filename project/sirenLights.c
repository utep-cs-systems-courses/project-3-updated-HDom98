#include <msp430.h>
#include "statemachines.h"
#include "led.h"
#include "buzzer.h"

//static char up;

void siren_advance()
{
  static char state = 0;
  switch(state)
    {
    case 0:/* state 1 red off */
      red_on = 0;
      led_update();
      up = 1;
      state++;
      break;
    case 1:/* state 2 red on, green off */
      red_on = 1;
      led_update();
      up = 0;
      state = 0;
    default:
      break;
    }
}
