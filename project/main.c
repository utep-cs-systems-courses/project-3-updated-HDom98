#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "statemachines.h"
#include "buzzer.h"

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
	 siren_on();
       }
     if(++count == 250)
       {
    	 siren_advance();
	 //redrawScreen = 1;
	 count = 0;
       }
     break;
    case 1:/* light dimming state */
      if((++count % 75) == 0) light_advance();
	
      if(++count == 250)
	{
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 2:/* blinking light state */
      if(++count == 125) light_advance();
        
      if(++count == 250)
	{
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 3:/* off state */
      buzz_off();
      if(++count == 250)
	{
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    default:
      break;    
    }
}
  

void main()
{
  configureClocks();
  lcd_init();
  led_init();
  switch_init();
  buzzer_init();

  green_on = 1;
  led_update();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  while (1) {			/* forever */
    if(redrawScreen)
      {
	redrawScreen = 0;
	switch(switch_state_down)
	  {
	  case 0:
	    // clearScreen(COLOR_RED);
	    break;
	    
	  case 1:
	    drawString5x7(20,20, "Hello", COLOR_RED, COLOR_PURPLE);
	    clearScreen(COLOR_PURPLE);
	    break;

	  case 2:
	    clearScreen(COLOR_BLACK);
	    drawString5x7(20,20, "WEE WOO", COLOR_GREEN, COLOR_BLACK);
	    drawString5x7(20,50, "WEE WOO", COLOR_PURPLE, COLOR_BLACK);
	    break;
	    
	  case 3:
	    clearScreen(COLOR_BLACK);
	    drawString5x7(20,20, "Goodbye", COLOR_GREEN, COLOR_BLACK);
	    break;
	  default:break;
	  }
  }
    green_on = 0;	/* green off */
    led_update();
    
    or_sr(0x10);       	/**< CPU OFF */
    
    green_on = 1;      	/* green on */
    led_update();
 }
}
