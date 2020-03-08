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
 * @brief - C Standard Library that declares several functions that are useful for testing and mapping characters.
 * @date  - 11-07-2017
 *
 */

#include "types.h"
#include "ctype.h"
#include "string_format.h"

/**************************************************************************************************
 *                  Defines
 **************************************************************************************************/

#define BASE_NUMBER_BITS_SIZE_HEX        ( 4 )
#define BASE_NUMBER_BITS_SIZE_OCT        ( 3 )
#define BASE_NUMBER_BITS_SIZE_BIN        ( 1 )

T_BOOL isdigit(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( ('0' <= c) && ('9' >= c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isxdigit(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if( (('0' <= c) && ('9' >= c)) || (('A' <= c) && ('F' >= c)) || (('a' <= c) && ('f' >= c)) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL iscdigit(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( ('0' <= c) && ('7' >= c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isbdigit(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( ('0' == c) || ('1' == c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isalpha(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( (TRUE == isupper(c)) || (TRUE == islower(c)) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isalnum(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( (TRUE == isdigit(c)) || (TRUE == isalpha(c)) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isupper(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( ('A' <= c) && ('Z' >= c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL islower(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( ('a' <= c) && ('z' >= c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL isspace(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( (' ' == c) || ('\t' == c) || ('\n' == c) || ('\r' == c) ) {

        ret = TRUE;
    }

    return ret;
}

T_BOOL ispunct(T_CHAR c)
{
    T_BOOL ret = FALSE;

    if ( (('!' <= c) && ('/' >= c)) || ((':' <= c) && ('@' >= c)) || (('[' <= c) && ('\'' >= c)) || (('{' <= c) && ('~' >= c)) ) {

        ret = TRUE;
    }

    return ret;
}

T_CHAR tolower(T_CHAR c)
{
    T_CHAR ret = c;

    if ( TRUE == isupper(ret) ) {

        ret += 32;
    }

    return ret;
}

T_CHAR toupper(T_CHAR c)
{
    T_CHAR ret = c;

    if ( TRUE == islower(ret) ) {

        ret -= 32;
    }

    return ret;
}

T_VOID strtolower(T_STRING str)
{
    while ( STRING_END != *str ) {

        *str = tolower(*str);
        str++;
    }
}

T_VOID strtoupper(T_STRING str)
{
    while ( STRING_END != *str ) {

        *str = toupper(*str);
        str++;
    }
}

