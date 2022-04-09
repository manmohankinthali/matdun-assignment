

#include "mcu.h"

//#define I2C_SLAVE_ADDRESS 0x68
//#define I2C_MAX_ADDRESS   0x7F
//#define I2C_SMBUS_ADDRESS 0x66

//#define I2C_TIME_OUT    0x7FFF

/* BAUD_RATE CALCULATIONS */
/* BAUD_RATE = (FREQ_BUS_CLK / (MUL * SCL Divider))
 * Assume MUL = 2 all the time
 * Baud_rate wants to configure for 9600 (or) 9.6 kHz
 * FREQ_BUS_CLK = 24MHz
 * SCL Divider = (FREQ_BUS_CLK / BAUD_RATE) / MUL.
 * This value should be matched with the list given in data
 * sheet and the corresponding ISR Value should be choosen. */

#define STANDARD_SPEED    // 100 kHz is the clock speed
//#define FAST_SPEED        // 400 kHz is the clock speed
//#define FAST_SPEED_PLUS   // 001 MHz is the clock speed

enum operation_e
{
  data_read,
  data_write
};

enum mode_e
{
  master_tx,
  master_rx,
  combined_format
};

enum i2c_status_e
{
  status_idle,
  in_transmit,
  in_transmit_to_read,
  transmit_complete,
  in_recieve,
  recieve_complete,
  no_ack
};

struct i2c_cmd_s
{
  uint8_t index;
  uint8_t frame_size;
  uint8_t *ptr;
  uint8_t slave_address;
  uint8_t register_address;
  enum i2c_status_e status;
  enum mode_e mode;
};

void
i2c0_init(void);

void
i2c0_interrupt_enable(void);

void
i2c0_master_mode(void);

void
i2c0_slave_mode(void);

void
i2c0_disable(void);

void
I2C0_IRQHandler(void);

void
i2c0_master_read_bytes(uint8_t slave_address, uint8_t size, uint8_t *ptr);

void
i2c0_master_combined_format(uint8_t slave_address,uint8_t size, uint8_t *ptr, uint8_t register_address);

void
i2c0_master_write_to_read(uint8_t slave_address, uint8_t *ptr);

void
i2c0_master_write_bytes(uint8_t slave_address, uint8_t size, uint8_t *ptr);


enum i2c_status_e
i2c0_get_status(void);

uint8_t
i2c0_recover(void);
