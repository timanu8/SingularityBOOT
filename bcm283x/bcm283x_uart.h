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
 * @brief - bcm2837 UART PL011 header file.
 * @date  - 27-02-2020
 *
 */

#ifndef __BCM283X_UART_H__
#define __BCM283X_UART_H__

#include "types.h"

/**
 * @brief bcm283x_uart_init - UART initialization function.
 * @param baud_rate
 * @return
 */
T_STATUS bcm283x_uart_init(T_ADDRESS dev, T_UINT64 clock_rate_hz, T_UINT32 baud_rate);

/**
 * @brief bcm283x_uart_send_char - UART Send char function with pooling mechanism.
 * @param c
 * @return
 */
T_VOID bcm283x_uart_send_char(T_ADDRESS dev, T_CHAR c);

/**
 * @brief bcm2837_uart_recv_char
 * @param dev
 * @return
 */
T_CHAR bcm283x_uart_recv_char(T_ADDRESS dev);

/**
 * @brief bcm283x_uart_send_string - UART Send string.
 * @param str
 * @return
 */
T_VOID bcm283x_uart_send_string(T_ADDRESS dev, T_STRING str);

#endif /* __BCM283X_UART_H__ */
