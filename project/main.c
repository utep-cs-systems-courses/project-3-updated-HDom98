#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

u_int shapeColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int count = 0;
  switch(switch_state_down)
    {
    case 0: /* siren state */
     if ((++count % 25) == 0)
       {
	 siren_on();
	 
       }
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
	clearScreen(COLOR_BLUE);
	//blink_advance();
      break;
    case 3:/* off state */
      buzz_off();
      break;
    default:
      break;
    
    }
  /*secCount ++;
  if (secCount == 250) {
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    shapeColor = (shapeColor == COLOR_GREEN) ? COLOR_RED : COLOR_BLACK;
    redrawScreen = 1;
    }*/
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

  // clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      
      drawString8x12(20,20, "hello", fontFgColor, COLOR_BLUE);
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
