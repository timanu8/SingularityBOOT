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
 * @brief - kprint function for kernel eraly debug.
 * @date  - 01-03-2020
 *
 */

#ifndef __KPRINT_H__
#define __KPRINT_H__

#include "types.h"

/**
 * @brief Register kprint device.
 * @param[in] cb - Reference to console print string function.
 */
T_VOID kprint_init(T_VOID (*cb)(T_STRING));

/**
 * @brief       Kernel simple string output function.
 * @param[in]   String to print.
 */
T_VOID kputs(T_STRING str);

/**
 * @brief Kernel formated output function.
 * @param[in] fmt - Format string to output.
 * @param[in] ... - List of variables defined in the format to add to the output.
 */
T_INT32 kprint(T_STRING fmt, ...);

#endif /* __KPRINT_H__ */
