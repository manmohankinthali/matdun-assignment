
#include "mcu.h"
#include "gpio.h"


void
gpio_init(void)
{

   /* ADP1650_ENABLE_PIN */
   GPIOA->PDDR |= ( OUTPUT << PIN_A7 );

   /* I2C_SDA_LINE */
   GPIOB->PDDR |= ( INPUT << PIN_B6 );

   /* I2C_SCL_LINE */
   GPIOB->PDDR |= (OUTPUT << PIN_B7 );
}



