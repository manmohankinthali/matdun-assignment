
#include "mcu.h"
#include <stdint.h>
#include "ics.h"

#define us_to_Hz(x) ((uint32_t)(1.0/(x*1E-6)))
#define PIT_COUNT(x) (FREQ_BUS_CLK / us_to_Hz(x))

void
pit_init(void);

void
pit_start(uint32_t value);

void
pit_stop(void);

void
PIT_CH0_IRQHandler(void);

uint8_t
pit_time_elapsed(void);

