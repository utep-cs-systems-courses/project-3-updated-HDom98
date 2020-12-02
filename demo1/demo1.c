/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and squares */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  drawString11x16(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(5, 40, 8, 50, COLOR_BLUE);
  fillRectangle(width - 13, 40, 8, 50, COLOR_RED);

  //u_char offc = 3;
  //u_char offr = 4;
  
  /*   for(u_char col = 0; col <= 10; col++)
    {
      drawPixel(10 + col, col, COLOR_RED);
      drawPixel(col, 10 - col, COLOR_RED);
    
      }*/

  /* right triangle  */
  /*
  for(u_char r = 0; r <= 11; r++)
    {
      for(u_char c = 0; c <= r; c++)
	{
	  drawPixel(r, c, COLOR_RED); 
	}
    }*/

  /* another triangle idk what its called 
  for(u_char r = 0; r < 10; r++)
    {
      for(u_char c = 0; c <= r; c++)
	{
	  drawPixel(10 - c, r, COLOR_RED);
	  drawPixel(10 + c, r, COLOR_RED);
	}
    } */

  u_char center = 5;
  for(u_char r = 0; r < 11; r++)
    {
      for(u_char c = 0; c <= 11; c++)
	{
	  drawPixel(c, r, COLOR_WHITE);  
	  drawPixel(r, c, COLOR_WHITE);
	}
    }

  for(u_char r = 0; r < center; r++)
    {
      for(u_char c = 0; c < center; c++)
	{
	  drawPixel(c + center, r + center, COLOR_BLACK);
	   drawPixel(c - center, r - center, COLOR_BLACK);
	}
    }
}
