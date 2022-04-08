

enum preset_level_e
{
  no_preset_mode,
  high_speed_mode,
  moderate_speed_mode,
  low_speed_mode
};

enum power_state_e
{
  power_off_e,
  power_on_e
};

void
app_init(void);

void
app_run(void);

uint8_t
serial_framing_callback(uint8_t *rx_ptr,uint8_t size);

uint8_t
app_get_power_on_state(void);

void
app_set_power_on_state(enum power_state_e state_e);

