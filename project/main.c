#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"

short redrawScreen = 1;

void wdt_c_handler()
{
  static int count = 0;
  switch(switch_state_down)
    {
    case 0: /* siren state */
     if ((++count % 25) == 0)
       {
	 green_on = 1;
	 led_update();
	 siren_on();
       }
     if (++count == 250)
       {
	 green_on = 1;
	 led_update();
	 siren_advance();
	 count = 0;
       }
     redrawScreen = 1;
     break;
    case 1:/* light dimming state */
      green_on = 1;
      led_update();
      
      if((++count % 75) == 0)
	light_advance();
      redrawScreen = 1;
      break;
    case 2:/* blinking light state */
      green_on = 1;
      led_update();
      
      if((++count % 50) == 0)
	clearScreen(COLOR_BLUE);
      clearScreen(COLOR_RED);
      redrawScreen = 1;
      break;
    case 3:/* off state */
      buzz_off();
      redrawScreen = 1;
      break;
    default:
      break;    
    }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  redrawScreen = 1;
  
  P1OUT &= ~LED_GREEN;	/* green off */
  or_sr(0x10);		/**< CPU OFF */
}
