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
 * @brief - bcm2837 GPU mailbox header file.
 * @date  - 01-03-2020
 *
 */

#include "types.h"
#include "values.h"
#include "error.h"
#include "bcm283x_gpu_mailbox.h"

/**************************************************************************************************
 *          Driver defines
 **************************************************************************************************/


/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

T_UINT32 mailbox_VC_to_ARM(T_UINT32 ptr);

/**************************************************************************************************
 *          Driver structures
 **************************************************************************************************/

typedef union
{
    /* Invidual bits */
    struct __gpu_mailbox_rw_reg
    {
        T_UINT32 channel:4;
        T_UINT32 data:28;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPU_MAILBOX_RW_REG;

typedef union
{
    /* Invidual bits */
    struct __gpu_mailbox_status_reg
    {
        T_UINT32 reserved:30;
        T_UINT32 empty:1;
        T_UINT32 full:1;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPU_MAILBOX_STATUS_REG;

typedef struct
{
    T_GPU_MAILBOX_RW_REG        read;                                               /* Data to receive from the GPU. */

    T_UINT32                    reserved0[((0x10 - 0x00) / 4) - 1];                 /* Used for the gap in reg address check datasheet. */

    T_GPU_MAILBOX_RW_REG        peak;                                               /* Work as read but without remove from the fifo. */
    T_UINT32                    sender;                                             /* Not documented */
    T_GPU_MAILBOX_STATUS_REG    status;                                             /* Tell if the mailbox is full or empty */
    T_UINT32                    config;                                             /* Not documented */
    T_GPU_MAILBOX_RW_REG        write;                                              /* Data to send to the GPU */
}T_GPU_MAILBOX;


typedef struct
{
    T_UINT32 tag_id;
    T_UINT32 buf_size;
    T_UINT32 data_size;
    T_UINT32 value;
}T_MB_MSG_TAG;

typedef struct
{
    T_UINT32        msg_size;
    T_UINT32        request;
    T_MB_MSG_TAG    tag;
    T_UINT32        end_tag;
}T_MB_MSG;

/**************************************************************************************************
 *          Driver Private variables
 **************************************************************************************************/

volatile T_GPU_MAILBOX* gpu_mb;

/**************************************************************************************************
 *          Public function implementation
 **************************************************************************************************/

T_VOID bcm283x_gpu_mailbox_init(T_ADDRESS dev)
{
    gpu_mb = (T_GPU_MAILBOX*)dev;
}

T_VOID bcm283x_gpu_mailbox_write(T_MAILBOX_CHANNEL channel, T_UINT32 data)
{
//    ASSERT(E_GPU_MB_CHANNEL_TOTAL > channel);

    if ( E_GPU_MB_CHANNEL_TOTAL > channel ) {

        T_GPU_MAILBOX_RW_REG    message;

        /* Convert pointer to VC addresses */
        data = mailbox_VC_to_ARM(data);

        /* Prepare message to send. */
        message.bits.channel = channel;
        message.bits.data    = (data >> VAL_4 );            /* Pass only the 28 most significant bits */

        /* Wait mailbox to have space to receive the message */
        while ( TRUE == gpu_mb->status.bits.full );

        /* Write the message to the mailbox. */
        gpu_mb->write = message;
    }
}

T_UINT32 bcm283x_gpu_mailbox_read(T_MAILBOX_CHANNEL channel)
{
    T_UINT32                ret = 0xFFFFFFFF;
    T_GPU_MAILBOX_RW_REG    data;

//    ASSERT(E_GPU_MB_CHANNEL_TOTAL > channel);

    if ( E_GPU_MB_CHANNEL_TOTAL > channel ) {

        do
        {
            /* Wait for a response on the mailbox. */
            while( (TRUE == gpu_mb->status.bits.empty) );

            data.all = gpu_mb->read.all;

        }while ( data.bits.channel != channel );

        ret = gpu_mb->read.all & 0xFFFFFFF0;                  /* Ignore the channel bits. */
    }

    return ret;
}


/**************************************************************************************************
 *          Private function implementation
 **************************************************************************************************/

T_UINT32 mailbox_VC_to_ARM(T_UINT32 ptr)
{
    return (ptr | 0xC0000000);
}



