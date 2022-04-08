/* Copyright (C) 2018 Invent Solutions Private Limited, Chennai.
 * All rights reserved.
 *
 * This program and the accompanying materials are made available
 * under the terms described in the LICENSE file which accompanies
 * this distribution. If the LICENSE file was not attached to this
 * distribution or for further clarifications, please contact
 * legal@inventsoln.com */

#ifndef BAJAJ_DESERT_COOLER_b52acef6_0cdb_11e9_9bba_74e6e2432146
#define BAJAJ_DESERT_COOLER_b52acef6_0cdb_11e9_9bba_74e6e2432146

#include "mcu.h"
#include <stdint.h>
#include "ics.h"

#define us_to_Hz(x) ((uint32_t)(1.0/(x*1E-6)))
#define PIT_COUNT(x) (FREQ_BUS_CLK / us_to_Hz(x))

void
pit_init(void);

void
pit_start(uint32_t value);

void
pit_stop(void);

void
PIT_CH0_IRQHandler(void);

uint8_t
pit_time_elapsed(void);

#endif // BAJAJ_DESERT_COOLER_b52acef6_0cdb_11e9_9bba_74e6e2432146
