
#include "app.h"
#include "ics.h"
#include "gpio.h"
#include "pit.h"
#include "adp_1650.h"


static inline void
app_logic(void);

static uint8_t    m_flasher;
static uint16_t   m_1ms_cntr;

void
app_init(void)
{
   pit_start(PIT_COUNT(1000));
   m_flasher = adp_1650_init();
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
   /* check if the init is performed proper */
   if(m_flasher)
   {
      /* counter to trigger strobe for every 10sec */
      m_1ms_cntr ++;
      if( m_1ms_cntr >= 10000)
      {
         m_1ms_cntr = 0;
         adp_1650_flash_on();
      }
   }
}

