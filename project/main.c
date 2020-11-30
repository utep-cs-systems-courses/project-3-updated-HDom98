#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "statemachines.h"
#include "buzzer.h"

short redrawScreen = 1;

u_char width = screenWidth, height = screenHeight;

u_int shapeColor1 = COLOR_RED;
u_int shapeColor2 = COLOR_GREEN;
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
	 redrawScreen = 1;
	 screenColor = COLOR_BLUE;
       }
     if(++count == 250)
       {
	 siren_advance();
	 screenColor = COLOR_RED;
	 redrawScreen = 1;
	 count = 0;
       }
     break;
    case 1:/* light dimming state */
      if(++count == 250)
	{
	  shapeColor1 = COLOR_BLUE;
	  shapeColor2 = COLOR_RED;
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 2:/* blinking light state */
      buzz_off();
      if(++count == 250)
	{
	  shapeColor1 = COLOR_PURPLE;
	  shapeColor2 = COLOR_PINK;
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 3:/* off state */
      buzz_off();
      if(++count == 250)
	{
	  shapeColor1 = COLOR_GREEN;
	  shapeColor2 = COLOR_WHITE;
	  redrawScreen = 1;
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

  red_on = 1; /* using red instead of green for cpu*/
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
	     clearScreen(screenColor);
          break;
	    
	  case 1:
	    drawSquare(shapeColor1,shapeColor2);
	    drawString5x7(20,20, "Hello", COLOR_RED, screenColor);
	    clearScreen(screenColor);
	    break;

	  case 2:
	    clearScreen(COLOR_BLACK);
	    drawString5x7(20,30, "WEE WOO", COLOR_BLUE, COLOR_BLACK);
	    drawString5x7(20,50, "WEE WOO", COLOR_RED, COLOR_BLACK);
	    drawSquare(shapeColor1,shapeColor2);
	    break;
	    
	  case 3:
	    clearScreen(COLOR_BLACK);
	    drawSquare(shapeColor1,shapeColor2);
	    drawString5x7(20,50, "Goodbye", COLOR_GREEN, COLOR_BLACK);
	    break;
	  default:break;
	  }
  }
    red_on = 0;	/* red off */
    led_update();
    
    or_sr(0x10);       	/**< CPU OFF */
    
    red_on = 1;      	/* red on */
    led_update();
 }
}

void drawSquare(u_int color1,u_int color2)
{
 u_char center = 15;
  for(u_char r = 20; r < 31; r++)
    {
      for(u_char c = 0; c <= 11; c++)
	{
	  drawPixel(c, r, color1);  
	  drawPixel(r, c, color1);
	}
    }

  for(u_char r = 0; r < center; r++)
    {
      for(u_char c = 0; c < center; c++)
	{
	  drawPixel(c + center, r + center, color2);
	  drawPixel(c - center, r - center, color2);
	}
    } 
}
