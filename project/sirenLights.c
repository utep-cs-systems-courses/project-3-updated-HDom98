#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"


void siren_advance()
{
  static char state = 0;
  switch(state)
    {
    case 0:/* state 1 red off */
      up = 1;
      state++;
      break;
    case 1:/* state 2 red on, green off */
      up = 0;
      state = 0;
    default:
      break;
    }
}