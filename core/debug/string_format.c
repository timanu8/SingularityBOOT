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

#include "types.h"
#include "values.h"
#include "error.h"
#include "string_format.h"
#include "stdlib.h"
#include "ctype.h"


/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

PRIVATE T_INT32 __format_string(T_STRING str, T_STRING ptr);
PRIVATE T_INT32 __format_number(T_STRING str, T_UINT64 val, T_UINT32 base);
PRIVATE T_INT32 __format_pointer(T_STRING str, T_UINT64 val);

PRIVATE T_UINT64 __parse_string(T_STRING in, T_STRING out);
PRIVATE T_UINT64 __parse_char(T_STRING in, T_CHAR* out);
PRIVATE T_UINT64 __parse_number(T_STRING in, T_UINT64* out);

/**************************************************************************************************
 *          Public functions implementation
 **************************************************************************************************/
T_INT32 string_format(T_STRING str, T_UINT32 buf_size, T_STRING fmt, va_list va)
{
    /* ret hold the number of chars that were formated into 1 string. */
    T_INT32 ret = ZERO;

    while ( (ret < (T_INT32)buf_size) && (STRING_END != *fmt) ) {

        if ( '%' != *fmt ) {

            /* Add to string and incremente string. fmt string will be incremented in the end of the loop. */
            *str++ = *fmt;
            /* Increment the number of formated chars. */
            ret++;
        }
        else {

            /* Get format type. */
            fmt++;

            /* String. */
            if ( 's' == *fmt ) {
                T_STRING ptr = va_arg(va, T_STRING);
                T_INT32  num;

                /* If string passed is null write string to tell. */
                if ( NULL != ptr ) {
                    num = __format_string(str, ptr);
                }
                else {
                    num = __format_string(str, "(null)");
                }

                /* Add to str the number of chars added. */
                str += num;

                /* Add to ret too. */
                ret += num;
            }
            /* Char. */
            else if ( 'c' == *fmt ) {

                *str++ = va_arg(va, T_INT32);
                ret++;
            }
            /* Hexadecimal number. */
            else if ( 'x' == *fmt ) {
                T_UINT32 val = va_arg(va, T_UINT64);
                T_INT32 n = __format_number(str, val, 16);
                str += n;
                ret += n;
            }
            /* Decimal number. */
            else if ( 'd' == *fmt ) {
                T_UINT32 val = va_arg(va, T_UINT64);
                T_INT32 n = __format_number(str, val, 10);
                str += n;
                ret += n;
            }
            /* Octal number. */
            else if ( 'o' == *fmt ) {
                T_UINT32 val = va_arg(va, T_UINT64);
                T_INT32 n = __format_number(str, val, 8);
                str += n;
                ret += n;
            }
            /* Binary number. */
            else if ( 'b' == *fmt ) {
                T_UINT32 val = va_arg(va, T_UINT64);
                T_INT32 n = __format_number(str, val, 2);
                str += n;
                ret += n;
            }
            /* Pointer formated for the architeture size */
            else if ( 'p' == *fmt ) {
                T_REGISTER val = va_arg(va, T_REGISTER);
                T_INT64 n = __format_pointer(str, val);
                str += n;
                ret += n;
            }
        }

        fmt++;
    }

    *str = STRING_END;

    return ret;
}

T_INT32 string_parse(T_STRING fmt, T_STRING input, va_list va)
{
    /* ret hold the number variables that were successfully matched. */
    T_INT32 ret = ZERO;

    /* Iterate on format string looking for the types to parse. */
    while( STRING_END != *fmt ) {

        /* Look for the char '%' where the char after will specify the type to parse. */
        while( ('%' != *fmt) && (STRING_END != *fmt) ) {
            fmt++;
        }

        /* Skip input white spaces. */
        while( (' ' == *input) || ('\t' == *input) || ('\n' == *input) ) {
            input++;
        }

        if( STRING_END != *fmt ) {

            /* Found % need to point to next char. */
            fmt++;

            /* Check the type to parse. */

            /* Parse a string. */
            if( 's' == *fmt ) {

                T_STRING ptr = va_arg(va, T_STRING);
                T_STATUS xret;

                xret = __parse_string(input, ptr);

                if( ZERO < xret ) {

                    /* Increment the number of parsed chars. */
                    input += xret;

                    /* If parse went OK increment the number of successfully parsed items. */
                    ret++;
                }
            }
            /* Parse a single char. */
            else if( 'c' == *fmt ) {

                T_CHAR* ptr = va_arg(va, T_CHAR*);
                T_STATUS xret;

                xret = __parse_char(input, ptr);

                if( ZERO < xret ) {

                    /* Increment the number of parsed chars. */
                    input += xret;

                    /* If parse went OK increment the number of successfully parsed items. */
                    ret++;
                }
            }
            /* Parse a number. */
            else if( ('d' == *fmt) || ('x' == *fmt) || ('o' == *fmt) || ('b' == *fmt) ) {

                T_UINT64* ptr = va_arg(va, T_UINT64*);
                T_STATUS xret;

                xret = __parse_number(input, ptr);

                if( ZERO < xret ) {

                    /* Increment the number of parsed chars. */
                    input += xret;

                    /* If parse went OK increment the number of successfully parsed items. */
                    ret++;
                }
            }
        }
    }

    return ret;
}

/**************************************************************************************************
 *          Private functions implementation
 **************************************************************************************************/

PRIVATE T_INT32 __format_string(T_STRING str, T_STRING ptr)
{
    T_INT32 ret = ZERO;

    /* Append the parameter string to the global one. */
    while ( (NULL != ptr) && (STRING_END != *ptr) ) {

        *str++ = *ptr++;
        ret++;
    }

    return ret;
}

PRIVATE T_INT32 __format_number(T_STRING str, T_UINT64 val, T_UINT32 base)
{
    T_INT32 ret = ZERO;
    T_CHAR  buf[VAL_64];

    /* Convert value to string. itoa handle all base number. */
    itoa(val,buf,base);

    T_STRING ptr = &buf[ZERO];

    /* Remove leading zeros. */
    while ( (STRING_END != *ptr) && ('0' == *ptr) ) {
        ptr++;
    }

    /* Copy converted value to formated string. */
    while ( STRING_END != *ptr ) {

        *str++ = *ptr++;
        ret++;
    }

    /* If ret == 0 none char was added. Cause of remove leading zeros need this option here. */
    if ( ZERO == ret ) {
        *str = '0';
        ret++;
    }

    return ret;
}

PRIVATE T_INT32 __format_pointer(T_STRING str, T_UINT64 val)
{
    T_INT32 ret = ZERO;
    T_CHAR  buf[sizeof(T_REGISTER) * VAL_4];
    T_STRING ptr = buf;

    /* Convert value to string in hexadecimal format */
    itoa(val,buf,VAL_16);

    /* Add 0x */
    *str++ = '0';
    *str++ = 'x';

    /* Update the number of added chars */
    ret += 2;

    /* Copy converted value to formated string. */
    while ( STRING_END != *ptr ) {

        *str++ = *ptr++;
        ret++;
    }

    return ret;
}


PRIVATE T_UINT64 __parse_string(T_STRING in, T_STRING out)
{
    T_UINT64 ret = ZERO;

    /* Parse string till find a space, newline, tab or end of string. */
    while( (STRING_END != *in) && ('\n' != *in) && ('\r' != *in) && ('\t' != *in) && (' ' != *in) ) {

        /* Assign the input char to the output string. */
        *out++ = *in++;

        /* Increment the number of parsed chars. */
        ret++;
    }

    return ret;
}

PRIVATE T_UINT64 __parse_char(T_STRING in, T_CHAR* out)
{
    T_UINT64 ret = ZERO;

    if( STRING_END != *in ) {

        /* Assign input char to output variable. */
        *out = *in;

        /* Increment the number of read chars. */
        ret++;
    }

    return ret;
}

PRIVATE T_UINT64 __parse_number(T_STRING in, T_UINT64* out)
{
    T_UINT64 ret = ZERO;

    /* Convert from string to int using std function. */
    *out = atoi(in);

    /* Count the number of chars that made the number. */
    while( (TRUE == isxdigit(*in)) || ('x' == *in) || ('X' == *in) || ('c' == *in) || ('C' == *in) || ('b' == *in) || ('B' == *in) || ('-' == *in) ) {

        /* Increment number of chars parsed. */
        ret++;

        /* Increment pointer to next char. */
        in++;
    }

    return ret;
}
