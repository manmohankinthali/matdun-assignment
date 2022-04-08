

#include "mcu.h"
#include <stdint.h>

#define OUTPUT 1
#define INPUT 0


#define PORT_A A
#define PORT_B A


#define PIN_A7 7
#define PIN_B6 14
#define PIN_B7 15





#define OUTPUT_SET(port,register_num) \
  FGPIO##port##_PSOR |=1<<register_num

#define OUTPUT_CLEAR(port,register_num) \
  FGPIO##port##_PCOR |=1<<register_num

#define OUTPUT_TOGGLE(port,register_num) \
  FGPIO##port##_PTOR |=1<<register_num


void
gpio_init(void);


