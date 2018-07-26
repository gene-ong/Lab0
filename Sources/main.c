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

// ***
// You will need to create a FIFO object with a size suitable to store 10 time-stamps using the packed time representation.
// ***

static void OneSecondElapsed(void)
{
  LEDs_Toggle(LED_BLUE);
  // One second has elapsed - update the time here
}

static void Button1Pressed(void)
{
  LEDs_Toggle(LED_ORANGE);
  // The button has been pressed - put a time-stamp into the FIFO
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
