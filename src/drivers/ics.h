
#include "mcu.h"


#define ICSOUTCLK_BDIV 0      // Divide ICSFLLCLK by 1
#define CORE_SYSTEM_CLK_DIV 0 // Divide ICSOUTCLK by 1
#define BUS_FLASH_CLK_DIV 1   // Divide ICSOUTCLK by 2
#define FTM_PWT_CLK_DIV 0     // Divide ICSOUTCLK by 1



#define ICS_ICR_CLK_Hz 37500

#define FLL_MULTIPLIER 1280

#define ICS_FLL_CLK (ICS_ICR_CLK_Hz * FLL_MULTIPLIER)
#define ICS_OUT_CLK ICS_FLL_CLK
#define FREQ_BUS_CLK (ICS_OUT_CLK/(1 << BUS_FLASH_CLK_DIV))


void
ics_init(void);


