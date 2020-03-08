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
 * @brief - Module that implement std lib functions.
 * @date  - 08-09-2017
 *
 */

#include "types.h"
#include "values.h"
#include "stdlib.h"
#include "ctype.h"
#include "string_format.h"


/**************************************************************************************************
 *          Defines
 **************************************************************************************************/
#define BITS_IN_HEX_DIGIT   4
#define BITS_IN_OCT_DIGIT   3
#define BITS_IN_BIN_DIGIT   1

#define BASE_BINARY         2
#define BASE_OCTAL          8
#define BASE_DECIMAL        10
#define BASE_HEXA           16

/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

PRIVATE T_CHAR __get_hex_char_from_value(T_UINT32 num);
PRIVATE T_VOID __itoa_hex(T_REGISTER val, T_STRING buffer);
PRIVATE T_VOID __itoa_oct(T_REGISTER val, T_STRING buffer);
PRIVATE T_VOID __itoa_bin(T_REGISTER val, T_STRING buffer);
PRIVATE T_VOID __itoa_dec(T_REGISTER val, T_STRING buffer);

PRIVATE T_INT64 __get_value_from_hex_char(T_CHAR c);
PRIVATE T_INT64 __atoi_hex(T_STRING buffer);
PRIVATE T_INT64 __atoi_oct(T_STRING buffer);
PRIVATE T_INT64 __atoi_bin(T_STRING buffer);
PRIVATE T_INT64 __atoi_dec(T_STRING buffer);


/**************************************************************************************************
 *          Public functions implementation
 **************************************************************************************************/

T_VOID itoa(T_REGISTER val, T_STRING buffer, T_UINT32 base)
{
    switch(base) {
    case BASE_BINARY:
        __itoa_bin(val, buffer);
        break;

    case BASE_OCTAL:
        __itoa_oct(val, buffer);
        break;

    case BASE_DECIMAL:
        __itoa_dec(val, buffer);
        break;

    case BASE_HEXA:
        __itoa_hex(val, buffer);
        break;

    default:
        break;
    }
}

T_INT64 atoi(T_STRING buffer)
{
    T_INT64 ret = ZERO;

    /* Check for special representations */
    if( '0' == *buffer ) {
        buffer++;
        if( ('x' == *buffer) || ('X' == *buffer) ) {
            ret = __atoi_hex(++buffer);
        }
        else if( ('c' == *buffer) || ('C' == *buffer) ) {
            ret = __atoi_oct(++buffer);
        }
        else if( ('b' == *buffer) || ('B' == *buffer) ) {
            ret = __atoi_bin(++buffer);
        }
        else {
            /* On UNIX systems normally if a number start with 0 is octal representation */
            ret = __atoi_oct(buffer);
        }
    }
    else {

        /* Check if the first char is a digit or any of the signals an integer can have, if not can return now. */
        if( (TRUE == isdigit(*buffer)) || ('-' == *buffer) || ('+' == *buffer) ) {
            ret = __atoi_dec(buffer);
        }
    }

    return ret;
}

/**************************************************************************************************
 *          Private functions implementation
 **************************************************************************************************/

PRIVATE T_CHAR __get_hex_char_from_value(T_UINT32 num)
{
    T_CHAR ret = '0';

    num &= 0x0F;

    if( 9 >= num ) {
        ret = num + '0';
    }
    else {
        ret = num - 10 + 'A';
    }

    return ret;
}

PRIVATE T_VOID __itoa_hex(T_REGISTER val, T_STRING buffer)
{
    /* Shift start at the highest 4 bits. */
    T_INT32 shift = BITS_IN_REG - BITS_IN_HEX_DIGIT;

    while( ZERO <= shift ) {
        *buffer++ = __get_hex_char_from_value((val >> shift));
        shift -= BITS_IN_HEX_DIGIT;
    }
    *buffer = '\0';
}

PRIVATE T_VOID __itoa_oct(T_REGISTER val, T_STRING buffer)
{
    /* Shift start at the highest 3 bits. Note 32 is not multiple of 3 so need to add 1 to make 33. */
    T_INT32 shift = BITS_IN_REG - BITS_IN_OCT_DIGIT + ONE;

    while( ZERO <= shift ) {
        *buffer++ = ((val >> shift) & 0x07) + '0';
        shift -= BITS_IN_OCT_DIGIT;
    }
    *buffer = '\0';
}

PRIVATE T_VOID __itoa_bin(T_REGISTER val, T_STRING buffer)
{
    /* Shift start at the highest bit. */
    T_INT32 shift = BITS_IN_REG - BITS_IN_BIN_DIGIT;

    while( ZERO <= shift ) {
        *buffer++ = ((val >> shift) & 0x01) + '0';
        shift -= BITS_IN_BIN_DIGIT;
    }
    *buffer = '\0';
}

PRIVATE T_VOID __swap_chars_in_str(T_STRING start, T_STRING end)
{
    while( start < end ) {
        T_CHAR aux = *end;
        *end = *start;
        *start = aux;

        start++;
        end--;
    }
}

PRIVATE T_VOID __itoa_dec(T_REGISTER val, T_STRING buffer)
{
    T_STRING ptr = buffer;

    do {
        *buffer++ = (val % 10) + '0';

        //val = div(val,10);
        val = val / 10;

    }while ( ZERO < val );

    *buffer = STRING_END;

    __swap_chars_in_str(ptr, buffer-ONE);

}


PRIVATE T_INT64 __get_value_from_hex_char(T_CHAR c)
{
    T_INT64 ret = ZERO;

    if( ('0' <= c) && ('9' >= c) ) {
        ret = (T_INT64)(c - '0');
    }
    else if( ('A' <= c) && ('F' >= c) ) {
        ret = (T_INT64)(c - 'A' + 10);
    }
    else if( ('a' <= c) && ('f' >= c) ) {
        ret = (T_INT64)(c - 'a' + 10);
    }

    return ret;
}

PRIVATE T_INT64 __atoi_hex(T_STRING buffer)
{
    T_INT64 ret = ZERO;

    while( TRUE == isxdigit(*buffer) ) {
        /* Shift ret to place the new digit */
        ret = ret << BITS_IN_HEX_DIGIT;
        /* Convert the new digit from string to value */
        ret += __get_value_from_hex_char(*buffer);
        /* Increment buffer to point to next digit */
        buffer++;
    }

    return ret;
}

PRIVATE T_INT64 __atoi_oct(T_STRING buffer)
{
    T_INT64 ret = ZERO;

    while( TRUE == iscdigit(*buffer) ) {
        /* Shift ret to place the new digit */
        ret = ret << BITS_IN_OCT_DIGIT;
        /* Convert the new digit from string to value */
        ret += (T_INT64)(*buffer - '0');
        /* Increment buffer to point to next digit */
        buffer++;
    }

    return ret;
}

PRIVATE T_INT64 __atoi_bin(T_STRING buffer)
{
    T_INT64 ret = ZERO;

    while( TRUE == isbdigit(*buffer) ) {
        /* Shift ret to place the new digit */
        ret = ret << BITS_IN_BIN_DIGIT;
        /* Convert the new digit from string to value */
        ret += (T_INT64)(*buffer - '0');
        /* Increment buffer to point to next digit */
        buffer++;
    }

    return ret;
}

PRIVATE T_INT64 __atoi_dec(T_STRING buffer)
{
    T_INT64 ret = ZERO;
    T_INT64 sig = ONE;

    /* Check for signal */
    if( '-' == *buffer ) {
        /* Signal the the intiger gonna be negative */
        sig = -ONE;
        /* Increment buffer to point for first digit */
        buffer++;
    }

    while( TRUE == isdigit(*buffer) ) {

        /* Multiply ret by 10 to make space for nes digit */
        ret *= 10;
        /* Place the new digit */
        ret += (*buffer - '0');
        /* Increment buffer to point for next digit */
        buffer++;
    }

    return (ret * sig);
}

