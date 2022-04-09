

#include "mcu.h"
#include <stdint.h>

#define OUTPUT 1
#define INPUT 0

#define PORT_A A
#define PORT_B A

#define PIN_A6 6
#define PIN_A7 7
#define PIN_B6 14
#define PIN_B7 15



void
gpio_init(void);

void
gpio_clear_enable_pin(void);

void
gpio_set_enable_pin(void);

void
gpio_set_strobe_pin(void);

void
gpio_clear_strobe_pin(void);

