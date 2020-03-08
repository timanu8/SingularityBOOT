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
 * @brief - Redefinition of data types.
 * @date  - 05-03-2020
 *
 */

#ifndef __TYPES_H__
#define __TYPES_H__

#include "cpu_properties.h"

/***************************************************************************************
 *  OS Data types redefined for better reading and easier to write. This file is for
 *  64bit architecture
 ***************************************************************************************/

typedef char                    T_CHAR;

typedef T_CHAR*                 T_STRING;

typedef unsigned char           T_BYTE;

typedef signed char             T_INT8;

typedef signed short int        T_INT16;

typedef signed int              T_INT32;

typedef signed long long int    T_INT64;

typedef unsigned char           T_UINT8;

typedef unsigned short int      T_UINT16;

typedef unsigned int            T_UINT32;

typedef unsigned long long int  T_UINT64;

typedef float                   T_FLOAT;

typedef double                  T_DOUBLE;

typedef T_INT32                 T_STATUS;

typedef void                    T_VOID;

typedef void*                   T_ADDRESS;

typedef T_UINT64                T_WORD;

typedef T_UINT64                T_SIZE;

typedef T_UINT64                T_BOOL;

typedef T_UINT64                T_STATE;

typedef T_CPU_REGISTER_WIDTH    T_REGISTER;

/***************************************************************************************
 *  Common initialization values.
 ***************************************************************************************/

/*
 *  ZERO value for common variables initialization.
 */
#ifndef ZERO
    #define ZERO  ( 0 )
#endif

/*
 *  ONE value for common variables initialization.
 */
#ifndef ONE
    #define ONE  ( 1 )
#endif

/*
 *  TWO value for common variables initialization.
 */
#ifndef TWO
    #define TWO  ( 2 )
#endif

/*
 *  ENABLE value for bit variable initialization.
 */
#ifndef ENABLE
    #define ENABLE  ( ONE )
#endif

/*
 *  DISABLE value for bit variable initialization.
 */
#ifndef DISABLE
    #define DISABLE  ( ZERO )
#endif

/*
 *  TRUE value.
 */
#ifndef TRUE
    #define TRUE  ( ONE  )
#endif

/*
 *  FALSE value.
 */
#ifndef FALSE
    #define FALSE ( ZERO )
#endif

/*
 *  NULL value.
 */
#ifndef NULL
    #define NULL  ((T_ADDRESS)ZERO)
#endif


/***************************************************************************************
 *  Keywords not C std bu usefull for reading code and avoid some stupid errors.
 ***************************************************************************************/

/*
 *  PRIVATE definition apllies to objects itended to be used only inside the module where
 *  they are declared.
 */
#ifndef PRIVATE
    #define PRIVATE static
#endif

/*
 *  LOCAL definition apllies to objects itended to be used only inside the module where
 *  they are declared, bu may be called indirectly by IRQs or FIQs.
 */
#ifndef LOCAL
    #define LOCAL static
#endif

/*
 *  STATIC apply only o INLINE functions declared in header files.
 */
#ifndef STATIC
    #define STATIC static
#endif


/*
 *  C INLINDE definition.
 */
#ifndef INLINE
    #define INLINE inline
#endif

/*
 *  C CONST definition.
 */
#ifndef CONST
    #define CONST const
#endif

/*
 *  C EXTERN definition.
 */
#ifndef EXTERN
    #define EXTERN extern
#endif

/*
 *  ROFIELD definition applies to make objects read only.
 */
#ifndef ROFIELD
    #define ROFIELD const
#endif

/*
 *  RWFIELD definition usefull for code reading.
 */
#ifndef RWFIELD
    #define RWFIELD
#endif

/*
 *  ROFIELD definition usefull for code reading.
 */
#ifndef WOFIELD
    #define WOFIELD
#endif

#endif /* __TYPES_H__ */
