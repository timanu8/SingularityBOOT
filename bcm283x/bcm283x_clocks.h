/*
 * MIT License
 *
 * Copyright (c) 2020 Tiago Vasconcelos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @brief - bcm2837 clock manager header file.
 * @date  - 01-03-2020
 *
 * In the raspberry pi the clocks are managed by the GPU, so every read/write
 * to the clock manager need to be in the form of commands to the GPU using
 * the correct mailbox and communication protocol.
 *
 */

#ifndef __BCM283X_CLOCKS_H__
#define __BCM283X_CLOCKS_H__

#include "types.h"

typedef enum
{
    E_CLOCK_EMMC   = 0x0001,
    E_CLOCK_UART   = 0x0002,
    E_CLOCK_ARM    = 0x0003,
    E_CLOCK_CORE   = 0x0004,
    E_CLOCK_V3D    = 0x0005,
    E_CLOCK_H264   = 0x0006,
    E_CLOCK_ISP    = 0x0007,
    E_CLOCK_SDRAM  = 0x0008,
    E_CLOCK_PIXEL  = 0x0009,
    E_CLOCK_PWM    = 0x000A,
}T_SOC_CLOCKS;

T_STATE bcm283x_get_clock_state(T_SOC_CLOCKS clock);

T_STATE bcm283x_set_clock_state(T_SOC_CLOCKS clock, T_STATE state);

T_UINT32 bcm283x_get_clock_rate(T_SOC_CLOCKS clock);

T_UINT32 bcm283x_get_clock_max_rate(T_SOC_CLOCKS clock);

T_UINT32 bcm283x_set_clock_rate(T_SOC_CLOCKS clock, T_UINT32 hz);

#endif /* __BCM283X_CLOCKS_H__ */
