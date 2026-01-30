/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Ref: https://github.com/raspberrypi/pico-sdk/blob/master/src/rp2_common/hardware_watchdog/watchdog.c
// Update https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#group_hardware_watchdog

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
