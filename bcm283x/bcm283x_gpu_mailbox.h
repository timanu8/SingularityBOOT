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
 * @brief - bcm2837 GPU mailbox header file.
 * @date  - 01-03-2020
 *
 */

#ifndef __BCM283X_GPU_MAILBOX_H__
#define __BCM283X_GPU_MAILBOX_H__

#include "types.h"

typedef enum {
    E_GPU_MB_CHANNEL_POWER      = 0x0,                                  /* Mailbox Channel 0: Power Management Interface        */
    E_GPU_MB_CHANNEL_FB         = 0x1,                                  /* Mailbox Channel 1: Frame Buffer                      */
    E_GPU_MB_CHANNEL_VUART      = 0x2,                                  /* Mailbox Channel 2: Virtual UART                      */
    E_GPU_MB_CHANNEL_VCHIQ      = 0x3,                                  /* Mailbox Channel 3: VCHIQ Interface                   */
    E_GPU_MB_CHANNEL_LEDS		= 0x4,									/* Mailbox Channel 4: LEDs Interface                    */
    E_GPU_MB_CHANNEL_BUTTONS	= 0x5,									/* Mailbox Channel 5: Buttons Interface                 */
    E_GPU_MB_CHANNEL_TOUCH      = 0x6,                                  /* Mailbox Channel 6: Touchscreen Interface             */
    E_GPU_MB_CHANNEL_COUNT      = 0x7,                                  /* Mailbox Channel 7: Counter                           */
    E_GPU_MB_CHANNEL_TAGS		= 0x8,									/* Mailbox Channel 8: Tags (ARM to VC)                  */
    E_GPU_MB_CHANNEL_GPU		= 0x9,									/* Mailbox Channel 9: GPU (VC to ARM)                   */

    E_GPU_MB_CHANNEL_TOTAL      = 0x0A
} T_MAILBOX_CHANNEL;

T_VOID bcm283x_gpu_mailbox_init(T_ADDRESS dev);

T_VOID bcm283x_gpu_mailbox_write(T_MAILBOX_CHANNEL channel, T_UINT32 data);

T_UINT32 bcm283x_gpu_mailbox_read(T_MAILBOX_CHANNEL channel);

#endif /* __BCM283X_GPU_MAILBOX_H__ */
