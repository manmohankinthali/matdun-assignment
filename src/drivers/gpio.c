
#include "mcu.h"
#include "gpio.h"


void
gpio_init(void)
{

   /* ADP1650_ENABLE_PIN */
   GPIOA->PDDR |= ( OUTPUT << PIN_A7 );

   /* ADP1650_STROBE_PIN */
   GPIOA->PDDR |= ( OUTPUT << PIN_A6 );

   /* I2C_SDA_LINE */
   GPIOB->PDDR |= ( INPUT << PIN_B6 );

   /* I2C_SCL_LINE */
   GPIOB->PDDR |= (OUTPUT << PIN_B7 );
}

void
gpio_clear_enable_pin(void)
{
   GPIOA->PCOR |= ( 1 << PIN_A7 );
}

void
gpio_set_enable_pin(void)
{
   GPIOA->PSOR |= ( 1 << PIN_A7 );
}

void
gpio_set_strobe_pin(void)
{
   GPIOA->PSOR |= ( 1 << PIN_A7 );
}

void
gpio_clear_strobe_pin(void)
{
   GPIOA->PCOR |= ( 1 << PIN_A6 );
}

