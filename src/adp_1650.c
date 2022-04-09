
#include "adp_1650.h"
#include "gpio.h"

#define ADP1650_ADDRESS    0x30
#define ADP1650_DEVICE_ID  0x22

#define SET_ENABLE         0x01
#define RESET_ENABLE       0x00

#define WRITE_BIT          0x01
#define READ_BIT           0x00


static inline void
adp_1650_set_enable_pin(void);

static inline uint8_t
adp_1650_check_device(void);

static inline uint8_t
adp_1650_reg_read(uint8_t dev_address, uint8_t reg_address, uint8_t size);

static inline void
adp_1650_reg_write(uint8_t dev_address, uint8_t reg_address, uint8_t data);


struct i2c_cmd_s adp_cmd_s;


uint8_t
adp_1650_init(void)
{
   uint8_t init_status = 1;

   /* enable gpio pin */
   adp_1650_set_enable_pin();

   /* init i2c with baudrate @ 100kbps */
   i2c0_init();

   /* adp device check */
   if(!adp_1650_check_device())
   {
      /* instead return the status to skip going further */
      init_status = 0;
      return (init_status);
   }


   // IO2, IO1 Cnfg = 0 :: High-Z
   // Flash Timer   = 4 :: 500ms
   adp_1650_reg_write(ADP1650_ADDRESS, 0x02, 0x04);

   // Flash Current Value = 4 :: 500mA
   // Torch Current Value = 4 :: 125mA
   adp_1650_reg_write(ADP1650_ADDRESS, 0x03, 0x24);

   // Inductor peak current limit   = 2  :: 2.75 A
   // Output Enable                 = 1  :: ON
   // Strobe Level                  = 0  :: Edge sensitive
   // Strobe Mode                   = 1  :: HW Strobe
   // LED Output Mode               = 3  :: Flash mode
   adp_1650_reg_write(ADP1650_ADDRESS, 0x04, 0x8F);

   return (init_status);
}

static inline void
adp_1650_set_enable_pin(void)
{
   static uint8_t count;

   /* set gpio as low */
   gpio_clear_enable_pin();
   /* give a delay of 250 clock cycles */
   for(count=0; count<250; count++);

   /* set gpio as high */
   gpio_set_enable_pin();
   /* give a delay of 100 clock cycles */
   for(count=0; count<100; count++);
}


static inline uint8_t
adp_1650_check_device(void)
{
   uint8_t device_check_status = 0;
   uint8_t device_id = 0x00;

   /* read the register from address 0x00 */
   device_id = adp_1650_reg_read(ADP1650_ADDRESS, 0x00, 1);

   if(ADP1650_DEVICE_ID == device_id)
   {
      device_check_status = 1;
   }

   return (device_check_status);
}


static inline uint8_t
adp_1650_reg_read(uint8_t dev_address, uint8_t reg_address, uint8_t size)
{
   uint8_t *ptr;

   /* i2c transfer to read data */
   i2c0_master_combined_format( dev_address, reg_address, ptr, 1);

   return (*ptr);
}

static inline void
adp_1650_reg_write(uint8_t dev_address, uint8_t reg_address, uint8_t data)
{
   /* i2c transfer to write data */
   i2c0_master_write_bytes( dev_address, data, (uint8_t *)&reg_address );
}


void
adp_1650_flash_on(void)
{
   /* trigger the strobe pin to turn on flash */
   gpio_set_strobe_pin();

   /* strobe delay (1ms) to consider as input for flash */
   uint16_t count;
   for(count=0; count<25000; count++);

   /* release the strobe pin */
   gpio_clear_strobe_pin();
}


