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

#include "types.h"
#include "error.h"
#include "stdarg.h"
#include "string_format.h"


#define KPRINT_BUFFER_SIZE  256


/* Function pointer to console output string */
T_VOID (*kprint_str)(T_STRING);

T_VOID kprint_init(T_VOID (*cb)(T_STRING))
{
    kprint_str = cb;
}

T_VOID kputs(T_STRING str)
{
    /* Print string safely. */
    kprint_str(str);
}

T_INT32 kprint(T_STRING fmt, ...)
{
    T_INT32 ret = OK;
    va_list va;
    T_CHAR  buffer[KPRINT_BUFFER_SIZE];

    /* Compiler generated list that give us the variable parameters passed to kprint. */
    va_start(va, fmt);

    ret = string_format(buffer, KPRINT_BUFFER_SIZE, fmt, va);

    /* Print string safely. */
    kprint_str(buffer);

    return ret;
}
