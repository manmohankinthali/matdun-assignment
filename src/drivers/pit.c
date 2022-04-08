
#include "pit.h"
#include "gpio.h"
#include "ics.h"
#include "interrupt.h"

#define  SCGC_PIT_CLOCK_ENABLE   0x02

static volatile uint8_t m_timeout;

void
pit_init (void)
{
   /* Enable clock control for PIT */
   SIM->SCGC |= (uint32_t)(1 << SIM_SCGC_PIT_SHIFT);

   /* Timer enabled and freezes during debug */
   PIT->MCR = PIT_MCR_FRZ_MASK;
} 

void
pit_start(uint32_t value)
{
   /* Timer is enabled with interrupts */
   PIT->CHANNEL->TCTRL = 0;
   PIT->CHANNEL->LDVAL = value;
   m_timeout = 0;
   interrupt_enable(PIT_CH0_IRQn, (uint8_t)interrupt_priority_1);
   PIT->CHANNEL->TCTRL = PIT_TCTRL_TIE_MASK|PIT_TCTRL_TEN_MASK;  
}

void
pit_stop(void)
{
   /* Disable the timer */
   PIT->CHANNEL->TCTRL = 0;
}

void
PIT_CH0_IRQHandler(void)
{
   PIT->CHANNEL->TFLG = PIT_TFLG_TIF_MASK;
   m_timeout = 1;
}

uint8_t
pit_time_elapsed(void)
{
   /* check if the timer is expired, to re-run again */
   if(m_timeout)
   {
      m_timeout = 0;
      return (1);
   }
   return (0);
}
