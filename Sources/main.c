/*!
** @file
** @version 1.0
** @brief
**         Main module.
**         This module implements a simple 12-hour clock.
**         It time-stamps button pushes and stores them in a FIFO used a packed representation.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


// CPU module - contains low level hardware initialization routines
#include "Cpu.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

// Simple timer
#include "timer.h"

// Button functions
#include "buttons.h"

// LED functions
#include "LEDs.h"

// The packed time representation

//   15             12   11                        6    5                       0
// |----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|
// |       hours       |          minutes            |          seconds            |

typedef uint16_t PackedTime_t;

// The Array required to store the 10 time-stamps
PackedTime_t Buffer[10];
// The counter to control where in the array the values should be stored
int Counter = 0;

// ***
// You will need to create a FIFO object with a size suitable to store 10 time-stamps using the packed time representation.
// ***

//Global Variable Declarations
uint8_t Seconds = 0;
uint8_t Minutes = 0;
uint8_t Hours = 0;

void FIFO_input(uint16_t time)
{
  Buffer[Counter] = time;
  Counter++;
  if (Counter>9)
    Counter = 0;
}

static void OneSecondElapsed(void)
{
  LEDs_Toggle(LED_BLUE);

  // One second has elapsed - update the time here
  Seconds++;
  if(Seconds>59)
    {
      Minutes++;
      Seconds = 0;
    }
  if(Minutes>59)
      {
        Hours++;
        Minutes = 0;
      }
  if(Hours>12)
      {
        Hours = 0;
      }

}

static void Button1Pressed(void)
{
  LEDs_Toggle(LED_ORANGE);
  // The button has been pressed - put a time-stamp into the FIFO
  PackedTime_t TimeStamp = 0;
  TimeStamp = (Hours<<12)|(Minutes<<6)|Seconds;
  FIFO_input(TimeStamp);
}

static void TowerInit(void)
{
  PE_low_level_init();
  Timer_Init(OneSecondElapsed);
  Buttons_Init(Button1Pressed);
  LEDs_Init();
  __EI();
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  TowerInit();
  /* Write your code here */
  for (;;)
  {
  }
}

/* END main */
/*!
** @}
*/
