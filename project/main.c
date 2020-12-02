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
  static int dimCount = 0;
  static int dimMode = 0;
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
      buzz_off();
      
      if((++count % 25) == 0 && dimMode == 1)
	{
	  light_advance();
	  dimCount++;
	}
      
       else  if((++count % 50) == 0 && dimMode == 2)
	{
	  light_advance();
	  dimCount++;
        }

      else if(dimMode == -1 || dimMode == 0)
	{/* led is off */
	  dimCount++;
	}
      
      if(dimCount == 3 && ++count == 250)
	{/* after 3 cycles change dim mode */
	  dimCount = 0;
	  dim(dimMode);
	}
      
      else if(++count == 250)
	{
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 2:/*shapes state */
      buzz_off();
      if(++count == 250)
	{
	  shapeColor1 = (shapeColor1 == COLOR_BLUE) ? COLOR_PURPLE : COLOR_RED;
	  shapeColor2 = (shapeColor2 == COLOR_RED) ? COLOR_PINK : COLOR_BLUE;
	  screenColor = (screenColor == COLOR_BLUE) ? COLOR_ORANGE : COLOR_RED;
	  redrawScreen = 1;
	  count = 0;
	}
      break;
    case 3:/* off state */
      buzz_off();
      shapeColor1 = (shapeColor1 == COLOR_PURPLE) ? COLOR_GREEN : COLOR_WHITE;
	  shapeColor2 = (shapeColor2 == COLOR_PINK) ? COLOR_WHITE : COLOR_RED;
      if(++count == 250)
	{
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
	    drawString5x7(20,20, "Hello", COLOR_RED, COLOR_GREEN);
	    clearScreen(COLOR_GREEN);
	    break;

	  case 2:
	    clearScreen(COLOR_BLACK);
	    drawString5x7(20,40, "WEE WOO", COLOR_BLUE, COLOR_BLACK);
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
