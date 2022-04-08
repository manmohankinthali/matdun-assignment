
#include "mcu.h"

#define VECTOR_TO_IRQ_MAP(x) (x-16)

#define ENABLE_INTERRUPTS  __enable_irq()
#define DISABLE_INTERRUPTS __disable_irq()


typedef enum
{
  /*lowest priority*/
  interrupt_priority_0, /**< enum for interrupt priority level 0 */
  interrupt_priority_1, /**< enum for interrupt priority level 1 */
  interrupt_priority_2, /**< enum for interrupt priority level 2 */
  interrupt_priority_3 /**< enum for interrupt priority level 3 */
  /*highest priority*/
}interrupt_priority;


void
interrupt_enable(IRQn_Type number, uint8_t priority);

void
interrupt_disable(IRQn_Type number);

