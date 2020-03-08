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
 * @brief - bcm2837 gpio controller interface file.
 * @date  - 27-02-2020
 *
 */

#ifndef __BCM283X_GPIO_H__
#define __BCM283X_GPIO_H__

#include "types.h"

/* Defines for GPIO Functions */
#define GPIO_INPUT                  (0b000)
#define GPIO_OUTPUT                 (0b001)
#define GPIO_ALT0                   (0b100)
#define GPIO_ALT1                   (0b101)
#define GPIO_ALT2                   (0b110)
#define GPIO_ALT3                   (0b111)
#define GPIO_ALT4                   (0b011)
#define GPIO_ALT5                   (0b010)

/* Pin values states */
#define GPIO_HIGH                   (ONE)
#define GPIO_LOW                    (ZERO)

/* Pull up/down configuration values */
#define GPIO_PULL_UP_DOWN_DISABLE   (0b00)
#define GPIO_PULL_DOWN_ENABLE       (0b01)
#define GPIO_PULL_UP_ENABLE         (0b10)
#define GPIO_PULL_UP_DOWN_RESERVED  (0b11)

T_VOID bcm283x_gpio_set_function(T_ADDRESS dev, T_UINT32 pin, T_UINT32 function);

T_VOID bcm283x_gpio_set_value(T_ADDRESS dev, T_UINT32 pin, T_UINT32 value);

T_VOID bcm283x_gpio_set_pull_up_down(T_ADDRESS dev, T_UINT32 pin, T_UINT32 value);


#endif /* __BCM283X_GPIO_H__ */
