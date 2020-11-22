#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;
  switch(switch_state_down)
    {
    case 0: /* siren state */
     if ((++count % 25) == 0) siren_on();
     if (++count == 250)
       {
	 siren_advance();
	 count = 0;
       }
     break;
    case 1:/* light dimming state */
      if((++count % 75) == 0)
	light_advance();
      break;
    case 2:/* blinking light state */
      if(++count == 125)
	blink_advance();
      break;
    case 3:/* off state */
      buzz_off();
      break;
    default:
      break;
    }
}
