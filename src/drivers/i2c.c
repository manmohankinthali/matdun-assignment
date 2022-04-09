
#include "i2c.h"
#include "mcu.h"
#include "interrupt.h"

struct i2c_cmd_s m_cmd_s;

void
i2c0_init(void)
{
   /* Clock enable for I2C0 */
   SIM->SCGC |= (1 << SIM_SCGC_I2C0_SHIFT );
   /* Pin selection for I2C0 */
   SIM->PINSEL0 |= (1 << SIM_PINSEL0_I2C0PS_SHIFT);

   /* Enabled I2C0 */
   I2C0->C1 = I2C_C1_IICEN_MASK;

   /* Defined for Standard Speed of 100Kbps */
   I2C0->F = I2C_F_MULT(0x00) | I2C_F_ICR(0x1F);
}

void
i2c0_interrupt_enable(void)
{
   /* Interrupt enable for I2C0 */
   I2C0->C1 |= I2C_C1_IICIE_MASK;
   interrupt_enable(I2C0_IRQn, (uint8_t)interrupt_priority_3);
}

void
I2C0_IRQHandler(void)
{
  if(I2C0->FLT & I2C_FLT_STOPF_MASK)
  {
    I2C0->FLT |= I2C_FLT_STOPF_MASK;
  }
  if(I2C0->FLT & I2C_FLT_STARTF_MASK)
  {
    I2C0->FLT |= I2C_FLT_STARTF_MASK;
  }
  I2C0->S |= I2C_S_IICIF_MASK;

  if(I2C0->C1 & I2C_C1_MST_MASK)
  {
    //master mode
    i2c0_master_mode();
  }
  else
  {
    //slave mode
    i2c0_slave_mode();
  }
}

void
i2c0_master_mode(void)
{
  if(I2C0->C1 & I2C_C1_TX_MASK)
  {
    if(m_cmd_s.index == m_cmd_s.frame_size)
    {
      I2C0->C1 &= ~(I2C_C1_MST_MASK | I2C_C1_IICIE_MASK);
      m_cmd_s.status = transmit_complete;
      return;
    }
    if(I2C0->S & I2C_S_RXAK_MASK)
    {
      I2C0->C1 &= ~(I2C_C1_MST_MASK | I2C_C1_IICIE_MASK);
      m_cmd_s.status = no_ack;
      return;
    }
    if(m_cmd_s.mode == combined_format)
    {
      if(!m_cmd_s.index)
      {
        I2C0->D = m_cmd_s.register_address;
        m_cmd_s.index++;
        return;
      }
      if(m_cmd_s.index == 1)
      {
        I2C0->C1 |= I2C_C1_RSTA_MASK;
        I2C0->D = ((m_cmd_s.slave_address & 0xFE) | 0x01);
        m_cmd_s.index++;
        return;
      }
      I2C0->C1 &= ~(I2C_C1_TX_MASK);
      I2C0->D;
      if(m_cmd_s.frame_size == 1)
      {
        I2C0->C1 |= I2C_C1_TXAK_MASK;
      }
      return;
    }
    if(m_cmd_s.mode == master_rx)
    {
      I2C0->C1 &= ~I2C_C1_TX_MASK;
      I2C0->D;
      if(m_cmd_s.frame_size == 1)
      {
        I2C0->C1 |= I2C_C1_TXAK_MASK;
      }
      return;
    }
    I2C0->D = *m_cmd_s.ptr;
    m_cmd_s.ptr ++;
    m_cmd_s.index ++;
  }
  else
  {
    m_cmd_s.index ++;
    if(m_cmd_s.index == m_cmd_s.frame_size)
    {
      I2C0->C1 &= ~(I2C_C1_MST_MASK | I2C_C1_IICIE_MASK);
      m_cmd_s.status = recieve_complete;
    }
    else if(m_cmd_s.index == m_cmd_s.frame_size-1)
    {
      I2C0->C1 |= I2C_C1_TXAK_MASK;
    }
    *m_cmd_s.ptr = I2C0->D;
    m_cmd_s.ptr ++;
  }
}

void
i2c0_slave_mode(void)
{
  if(I2C0->S & I2C_S_ARBL_MASK)
  {
    I2C0->S |= I2C_S_ARBL_MASK;
  }
  I2C0->C1 = 0;
}

void
i2c0_master_read_bytes(uint8_t slave_address, uint8_t size, uint8_t *ptr)
{
  if(!size)
  {
    return;
  }

  m_cmd_s.mode = master_rx;
  m_cmd_s.index = 0;
  m_cmd_s.frame_size = size;
  m_cmd_s.status = in_recieve;
  m_cmd_s.ptr = ptr;
  m_cmd_s.slave_address = slave_address;

  I2C0->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK
            | I2C_C1_MST_MASK | I2C_C1_TX_MASK;

  I2C0->D = (slave_address & 0xFE) | 0x01;
}

void
i2c0_master_write_to_read(uint8_t slave_address, uint8_t *ptr)
{
  m_cmd_s.mode = master_tx;
  m_cmd_s.index = 0;
  m_cmd_s.frame_size = 1;
  m_cmd_s.status = in_transmit_to_read;
  m_cmd_s.ptr = ptr;
  m_cmd_s.slave_address = slave_address;

  I2C0->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK
            | I2C_C1_MST_MASK | I2C_C1_TX_MASK | I2C_C1_RSTA_MASK;

  I2C0->D = (slave_address & 0xFE);
}

void
i2c0_master_write_bytes(uint8_t slave_address, uint8_t size, uint8_t *ptr)
{
  m_cmd_s.mode = master_tx;
  m_cmd_s.index = 0;
  m_cmd_s.frame_size = size;
  m_cmd_s.status = in_transmit;
  m_cmd_s.ptr = ptr;
  m_cmd_s.slave_address = slave_address;

  I2C0->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK
            | I2C_C1_MST_MASK | I2C_C1_TX_MASK;

  I2C0->D = (slave_address & 0xFE);
}

void
i2c0_master_combined_format(uint8_t slave_address,uint8_t size, uint8_t *ptr, uint8_t register_address)
{
  m_cmd_s.mode = combined_format;
  m_cmd_s.index = 0;
  m_cmd_s.frame_size = size+2;
  m_cmd_s.status = in_transmit;
  m_cmd_s.ptr = ptr;
  m_cmd_s.slave_address = slave_address;
  m_cmd_s.register_address = register_address;

  I2C0->C1 |= I2C_C1_IICEN_MASK | I2C_C1_IICIE_MASK
            | I2C_C1_MST_MASK | I2C_C1_TX_MASK;

  I2C0->D = (slave_address & 0xFE);
}

void
i2c0_disable(void)
{
  I2C0->C1 = 0;
  m_cmd_s.status = status_idle;
}

enum i2c_status_e
i2c0_get_status(void)
{
  return (m_cmd_s.status);
}

uint8_t
i2c0_recover(void)
{
  uint16_t timeout;

  if(I2C0->FLT & I2C_FLT_STOPF_MASK)
  {
    I2C0->FLT |= I2C_FLT_STOPF_MASK;
  }
  if(I2C0->FLT & I2C_FLT_STARTF_MASK)
  {
    I2C0->FLT |= I2C_FLT_STARTF_MASK;
  }
  I2C0->S |= I2C_S_IICIF_MASK;

  I2C0->C1 = I2C_C1_MST_MASK | I2C_C1_IICEN_MASK
            | I2C_C1_TXAK_MASK;

  I2C0->D;

  while(!(I2C0->S & I2C_S_IICIF_MASK))
  {
    timeout ++;
    if(timeout > 1000)
    {
      I2C0->C1 &= ~I2C_C1_MST_MASK;
      return (0);
    }
  }
  I2C0->C1 &= ~I2C_C1_MST_MASK;
  return (1);
}
