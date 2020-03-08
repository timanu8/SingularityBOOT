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
 * @brief - Module that implement string parse and manipulaion functions for std libraries.
 * @date  - 05-07-2017
 *
 */

#ifndef __STRING_FORMAT_H__
#define __STRING_FORMAT_H__

#include "types.h"
#include "stdarg.h"

/** @brief End of string macro. */
#define STRING_END ('\0')

/** @brief End of line macro. */
#define STRING_EOL ('\n')

/** @brief Carriage return macro. */
#define STRING_CR  ('\r')



/**
 * @brief Function to format output for std functions
 * @param[out] str - Buffer to hold formated string
 * @param[in] buf_size - Max size for buffer
 * @param[in] fmt - Format string to output
 * @param[in] va - List of variables defined in the format to add to the output
 */
T_INT32 string_format(T_STRING str, T_UINT32 buf_size, T_STRING fmt, va_list va);

/**
 * @brief string_parse - Parse an input string and assign the values to the correct variables.
 * @param [in]fmt - Buffer that hold the format string
 * @param [in]input - Buffer that hold the input string with data
 * @param [in]va - List of variables defined in the format to parse
 * @return
 */
T_INT32 string_parse(T_STRING fmt, T_STRING input, va_list va);

#endif /* __STRING_FORMAT_H__ */
