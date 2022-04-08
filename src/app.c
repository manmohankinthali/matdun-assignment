#include <stdint.h>
#include <string.h>
#include "app.h"
#include "ics.h"
#include "gpio.h"
#include "pit.h"

static inline void
app_logic(void);


void
app_init(void)
{
   pit_start(PIT_COUNT(1000));
}

void
app_run(void)
{
   while(1)
   {
      if(pit_time_elapsed())
      {
         /* Process Functions */
         /* This loop runs @ every 1ms */
         app_logic();

      }
   }
}

static inline void
app_logic(void)
{

}

