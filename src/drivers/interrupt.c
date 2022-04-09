
#include "interrupt.h"
#include "fsl_device_registers.h"       // Device header
#include "core_cm0plus.h"


void
interrupt_enable(IRQn_Type number, uint8_t priority)
{
   SIM->SCGC |= (uint32_t)(1 << SIM_SCGC_PIT_SHIFT);

   /* Interrupt Clear Pending Register */
  NVIC_ClearPendingIRQ (number);

  /* Set interrupt priority level */
  NVIC_SetPriority (number, priority);

  /* Interrupt Set Enable Register */
  NVIC_EnableIRQ(number);
}


void
interrupt_disable(IRQn_Type number)
{
  /* Disable Interrupt */
  NVIC_DisableIRQ(number);
}
