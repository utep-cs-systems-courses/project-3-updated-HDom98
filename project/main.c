#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"

short redrawScreen = 1;

u_int fontFgColor = COLOR_RED;
u_int screenColor = COLOR_BLUE;

void wdt_c_handler()
{
  static int count = 0;
  switch(switch_state_down)
    {
    case 0: /* siren state */	 
     if ((++count % 25) == 0)
       {
	 screenColor = (screenColor == COLOR_BLUE) ? COLOR_BLUE : COLOR_RED;
	 siren_on();
       }
     if (++count == 125)
       {
	 siren_advance();
	 count = 0;
       }
     redrawScreen = 1;
     break;
    case 1:/* light dimming state */
      fontFgColor = COLOR_RED;
      screenColor = COLOR_GREEN;
      
      if((++count % 75) == 0)
	light_advance();
      redrawScreen = 1;
      break;
    case 2:/* blinking light state */
      if((++count % 50) == 0){
	 fontFgColor = COLOR_RED;
	 screenColor = COLOR_BLUE;
	 redrawScreen = 1;
      }
      
      fontFgColor = COLOR_BLUE;
      screenColor = COLOR_RED;
      redrawScreen = 1;
      
      break;
    case 3:/* off state */

      //screenColor = COLOR_BLACK;
      //fontFgColor = COLOR_GREEN;
      
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

  while (1) {			/* forever */
    if(redrawScreen)
      {
	redrawScreen = 0;
	switch(switch_state_down)
	  {
	  case 0:
	    clearScreen(screenColor);
	    break;

	  case 1:
	    drawString5x7(20,20, "Hello", fontFgColor, screenColor);
	    clearScreen(screenColor);
	    break;

	  case 2:
	    drawString5x7(20,20, "WEE WOO", fontFgColor, screenColor);
	    drawString5x7(20,50, "WEE WOO", fontFgColor, screenColor);
	    break;
	  case 3:
	    clearScreen(COLOR_BLACK);
	    drawString5x7(20,20, "Goodbye", COLOR_GREEN, COLOR_BLACK);
	    break;
	  default:break;
	  }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
 }
}
