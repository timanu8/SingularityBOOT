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
 * @brief - Common used values for increase code readability.
 * @date  - 05-03-2020
 *
 */

#ifndef __VALUES_H__
#define __VALUES_H__

#include "types.h"

/* Common values. */
#define VAL_1           ( 1             )
#define VAL_2           ( 2             )
#define VAL_4           ( 4             )
#define VAL_8           ( 8             )
#define VAL_16          ( 16            )
#define VAL_32          ( 32            )
#define VAL_64          ( 64            )
#define VAL_128         ( 128           )
#define VAL_256         ( 256           )
#define VAL_512         ( 512           )

#define VAL_1K          ( 1024          )
#define VAL_2K          ( 2048          )
#define VAL_4K          ( 4096          )
#define VAL_8K          ( 8192          )
#define VAL_16K         ( 16384         )
#define VAL_32K         ( 32768         )
#define VAL_64K         ( 65536         )
#define VAL_128K        ( 131072        )
#define VAL_256K        ( 262144        )
#define VAL_512K        ( 524288        )

#define VAL_1M          ( 1048576       )
#define VAL_2M          ( 2097152       )
#define VAL_4M          ( 4194304       )
#define VAL_8M          ( 8388608       )
#define VAL_16M         ( 16777216      )
#define VAL_32M         ( 33554432      )
#define VAL_64M         ( 67108864      )
#define VAL_128M        ( 134217728     )
#define VAL_256M        ( 268435456     )
#define VAL_512M        ( 536870912     )

#define VAL_1G          ( 1073741824    )
#define VAL_2G          ( 2147483648    )
#define VAL_4G          ( 4294967296    )

/* Bits present in architeture register */
#define BITS_IN_REG     (sizeof(T_REGISTER) * VAL_8)

#endif /* __VALUES_H__ */
