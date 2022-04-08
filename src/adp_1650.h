
#include <stdint.h>



void
adp_1650_init(void);


uint8_t
adp_1650_reg_read(uint8_t dev_address, uint8_t reg_address);


uint8_t
adp_1650_reg_write(uint8_t dev_address, uint8_t reg_address, uint8_t data);

