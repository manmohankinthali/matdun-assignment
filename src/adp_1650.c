
#include <adp_1650.h>

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



void
adp_1650_init(void)
{
   uint8_t init_status = 1;

   /* enable gpio pin */
   adp_1650_set_enable_pin();

   /* init i2c with baudrate @ 100kbps */

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
   // Strobe Mode                   = 1  :: HW Strobe
   // LED Output Mode               = 3  :: Flash mode
   adp_1650_reg_write(ADP1650_ADDRESS, 0x04, 0x8F);

   return (init_status);
}

static inline void
adp_1650_set_enable_pin(void)
{
   /* gpio port set as output */
   /* set gpio as low */
   /* give a delay of 500 clock cycles */
   /* set gpio as high */
   /* give a delay of 100 or 250 clock cycles */
}


static inline uint8_t
adp_1650_check_device(void)
{
   uint8_t device_check_status = 0;
   uint8_t device_id = 0x00;

   /* read the register 0x00 */
   device_id = 0x22;

   if(ADP1650_DEVICE_ID == device_id)
   {
      device_check_status = 1;
   }

   return (device_check_status);
}


uint8_t
adp_1650_reg_read(uint8_t dev_address, uint8_t reg_address)
{
   dev_address = ( dev_address << 1 ) | WRITE_BIT;

   /* i2c transfer to write data */
}

uint8_t
adp_1650_reg_write(uint8_t dev_address, uint8_t reg_address, uint8_t data)
{
   dev_address = ( dev_address << 1 ) | READ_BIT;

   /* i2c transfer to read data */
}















