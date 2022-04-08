
#include "ics.h"
#include "gpio.h"
#include "app.h"

int
main(void)
{
  ics_init();
  gpio_init();
  app_init();
  app_run();
}
