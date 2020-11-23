#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  //switch_init();
  //led_init();
  //buzzer_init();
  
  //enableWDTInterrupts();	/* enable periodic interrupt */
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);

  drawString8x12(20,20, "hello", COLOR_GREEN, COLOR_RED);
  fillRectangle(5, 40, 8, 50, COLOR_BLUE);
  fillRectangle(width - 13, 40, 8, 50, COLOR_RED);

  or_sr(0x18);		/* CPU off, GIE on */
}
