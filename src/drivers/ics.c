

#include "ics.h"


enum ics_c1_irefs
{
  ics_c1_iref_external,
  ics_c1_iref_internal
};

enum ics_c1_clks
{
  ics_c1_clks_fll_output,
  ics_c1_clks_internal_reference_clk,
  ics_c1_clks_external_reference_clk,
  ics_c1_clks_reserved
};

enum ics_c1_irclken
{
  ics_c1_irc_disabled,
  ics_c1_irc_enabled
};


void
ics_init(void)
{
   /* SIM NMI Disable */
   SIM->SOPT0 &= ~(SIM_SOPT0_NMIE_MASK);

   /* define clock frequency to 24 MHz */
   ICS->C1 = ((uint8_t)ics_c1_iref_internal << ICS_C1_IREFSTEN_SHIFT)
              | ICS_C1_CLKS((uint8_t)ics_c1_clks_fll_output)
              | ((uint8_t)ics_c1_irc_enabled << ICS_C1_IRCLKEN_SHIFT)                                                                      
              | (ICS_C1_IREFS_MASK);

   /* wait for FLL to lock */
   while (!(ICS->S & ICS_S_LOCK_MASK));

   /* Avoid Clock frequency to cross 24 MHz */
   SIM->CLKDIV = SIM_CLKDIV_OUTDIV1(CORE_SYSTEM_CLK_DIV)
              | (BUS_FLASH_CLK_DIV << 2);

   /* Bus frequency divides by 1 */
   ICS->C2 = 0;
}
