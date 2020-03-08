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
 * @brief - bcm2837 clock manager implementation file.
 * @date  - 01-03-2020
 *
 * In the raspberry pi the clocks are managed by the GPU, so every read/write
 * to the clock manager need to be in the form of commands to the GPU using
 * the correct mailbox and communication protocol.
 *
 */

#include "types.h"
#include "values.h"
#include "error.h"
#include "bcm283x_clocks.h"
#include "bcm283x_gpu_mailbox.h"

/**************************************************************************************************
 *          Driver defines
 **************************************************************************************************/


/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/


/**************************************************************************************************
 *          Driver structures
 **************************************************************************************************/

enum
{
    E_CLOCK_CMD_GET_CLOCK_STATE         = 0x00030001,
    E_CLOCK_CMD_SET_CLOCK_STATE         = 0x00038001,
    E_CLOCK_CMD_GET_CLOCK_RATE          = 0x00030002,
    E_CLOCK_CMD_GET_CLOCK_MAX_RATE      = 0x00030004,
    E_CLOCK_CMD_SET_CLOCK_RATE          = 0x00038002,
};

typedef struct
{
    T_UINT32 msg_size;
    T_UINT32 res;
    T_UINT32 cmd;
    T_UINT32 resp_size;     /* Response size */
    T_UINT32 req_size;      /* Request size */
    T_UINT32 clock_id;
    T_UINT32 clock_state;
    T_UINT32 end_val;       /* should be 0 */
}T_CLOCK_STATE_CMD;

typedef struct
{
    T_UINT32 msg_size;
    T_UINT32 res;
    T_UINT32 cmd;
    T_UINT32 resp_size;     /* Response size */
    T_UINT32 req_size;      /* Request size */
    T_UINT32 clock_id;
    T_UINT32 clock_val;
    T_UINT32 end_val;       /* should be 0 */
}T_READ_CLOCK_CMD;

typedef struct
{
    T_UINT32 msg_size;
    T_UINT32 res;
    T_UINT32 cmd;
    T_UINT32 resp_size;     /* Response size */
    T_UINT32 req_size;      /* Request size */
    T_UINT32 clock_id;
    T_UINT32 clock_val;
    T_UINT32 skip_turbo;
    T_UINT32 end_val;       /* should be 0 */
}T_SET_CLOCK_CMD;

/**************************************************************************************************
 *          Driver Private variables
 **************************************************************************************************/

static T_UINT32 __attribute__((aligned(VAL_16))) mailbox_message[VAL_16];

/**************************************************************************************************
 *          Public function implementation
 **************************************************************************************************/

T_STATE bcm283x_get_clock_state(T_SOC_CLOCKS clock)
{
    T_STATE ret             = DISABLE;
    T_CLOCK_STATE_CMD* cmd  = (T_CLOCK_STATE_CMD*)mailbox_message;

    cmd->msg_size       = sizeof(T_CLOCK_STATE_CMD);
    cmd->res            = ZERO;
    cmd->cmd            = E_CLOCK_CMD_GET_CLOCK_STATE;
    cmd->resp_size      = VAL_8;
    cmd->req_size       = VAL_4;
    cmd->clock_id       = clock;
    cmd->clock_state    = ZERO;
    cmd->end_val        = ZERO;

    /* Send command to the GPU */
    bcm283x_gpu_mailbox_write(E_GPU_MB_CHANNEL_TAGS, (T_UINT32)((T_UINT64)cmd));

    /* Wait GPU answer */
    bcm283x_gpu_mailbox_read(E_GPU_MB_CHANNEL_TAGS);

    ret = cmd->clock_state;

    return ret;
}

T_STATE bcm283x_set_clock_state(T_SOC_CLOCKS clock, T_STATE state)
{
    T_STATE ret             = DISABLE;
    T_CLOCK_STATE_CMD* cmd  = (T_CLOCK_STATE_CMD*)mailbox_message;

    cmd->msg_size       = sizeof(T_CLOCK_STATE_CMD);
    cmd->res            = ZERO;
    cmd->cmd            = E_CLOCK_CMD_SET_CLOCK_STATE;
    cmd->resp_size      = VAL_8;
    cmd->req_size       = VAL_8;
    cmd->clock_id       = clock;
    cmd->clock_state    = (T_UINT32)state;
    cmd->end_val        = ZERO;

    /* Send command to the GPU */
    bcm283x_gpu_mailbox_write(E_GPU_MB_CHANNEL_TAGS, (T_UINT32)((T_UINT64)cmd));

    /* Wait GPU answer */
    bcm283x_gpu_mailbox_read(E_GPU_MB_CHANNEL_TAGS);

    ret = cmd->clock_state;

    return ret;
}

T_UINT32 bcm283x_get_clock_rate(T_SOC_CLOCKS clock)
{
    T_UINT32 ret            = ZERO;
    T_READ_CLOCK_CMD* cmd   = (T_READ_CLOCK_CMD*)mailbox_message;

    cmd->msg_size       = sizeof(T_READ_CLOCK_CMD);
    cmd->res            = ZERO;
    cmd->cmd            = E_CLOCK_CMD_GET_CLOCK_RATE;
    cmd->resp_size      = VAL_8;
    cmd->req_size       = VAL_4;
    cmd->clock_id       = clock;
    cmd->clock_val      = ZERO;
    cmd->end_val        = ZERO;

    /* Send command to the GPU */
    bcm283x_gpu_mailbox_write(E_GPU_MB_CHANNEL_TAGS, (T_UINT32)((T_UINT64)cmd));

    /* Wait GPU answer */
    bcm283x_gpu_mailbox_read(E_GPU_MB_CHANNEL_TAGS);

    ret = cmd->clock_val;

    return ret;
}

T_UINT32 bcm283x_get_clock_max_rate(T_SOC_CLOCKS clock)
{
    T_UINT32 ret            = ZERO;
    T_READ_CLOCK_CMD* cmd   = (T_READ_CLOCK_CMD*)mailbox_message;

    cmd->msg_size       = sizeof(T_READ_CLOCK_CMD);
    cmd->res            = ZERO;
    cmd->cmd            = E_CLOCK_CMD_GET_CLOCK_MAX_RATE;
    cmd->resp_size      = VAL_8;
    cmd->req_size       = VAL_4;
    cmd->clock_id       = clock;
    cmd->clock_val      = ZERO;
    cmd->end_val        = ZERO;

    /* Send command to the GPU */
    bcm283x_gpu_mailbox_write(E_GPU_MB_CHANNEL_TAGS, (T_UINT32)((T_UINT64)cmd));

    /* Wait GPU answer */
    bcm283x_gpu_mailbox_read(E_GPU_MB_CHANNEL_TAGS);

    ret = cmd->clock_val;

    return ret;
}

T_UINT32 bcm283x_set_clock_rate(T_SOC_CLOCKS clock, T_UINT32 hz)
{
    T_UINT32 ret            = ZERO;
    T_SET_CLOCK_CMD* cmd   = (T_SET_CLOCK_CMD*)mailbox_message;

    cmd->msg_size       = sizeof(T_SET_CLOCK_CMD);
    cmd->res            = ZERO;
    cmd->cmd            = E_CLOCK_CMD_SET_CLOCK_RATE;
    cmd->resp_size      = VAL_8;
    cmd->req_size       = VAL_4;
    cmd->clock_id       = clock;
    cmd->clock_val      = hz;
    cmd->skip_turbo     = ZERO;
    cmd->end_val        = ZERO;

    /* Send command to the GPU */
    bcm283x_gpu_mailbox_write(E_GPU_MB_CHANNEL_TAGS, (T_UINT32)((T_UINT64)cmd));

    /* Wait GPU answer */
    bcm283x_gpu_mailbox_read(E_GPU_MB_CHANNEL_TAGS);

    ret = cmd->clock_val;

    return ret;
}

/**************************************************************************************************
 *          Private function implementation
 **************************************************************************************************/


