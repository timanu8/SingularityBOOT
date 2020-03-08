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
 * @brief - bcm2837 UART PL011 implementation file.
 * @date  - 27-02-2020
 *
 */

#include "types.h"
#include "values.h"
#include "error.h"
#include "bcm283x_uart.h"

/**************************************************************************************************
 *          UART defines
 **************************************************************************************************/

/* Define for the UART clock this value was geted on rpi bare metal forum. link: https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=164115&p=1060023&hilit=uartx01#p1060023 */
#define UART_BASE_CLOCK_HZ      48000000

/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

/**************************************************************************************************
 *          UART structures
 **************************************************************************************************/

typedef union
{
    /* Invidual bits */
    struct __uart_data_reg
    {
        T_UINT32 data:8;
        T_UINT32 fe:1;
        T_UINT32 pe:1;
        T_UINT32 be:1;
        T_UINT32 oe:1;
        T_UINT32 reserved:20;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_DATA_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_rsrecr_reg
    {
        T_UINT32 fe:1;
        T_UINT32 pe:1;
        T_UINT32 be:1;
        T_UINT32 oe:1;
        T_UINT32 reserved:28;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_RSRECR_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_fr_reg
    {
        T_UINT32 cts:1;
        T_UINT32 dsr:1;
        T_UINT32 dcd:1;
        T_UINT32 busy:1;
        T_UINT32 rxfe:1;
        T_UINT32 txff:1;
        T_UINT32 rxff:1;
        T_UINT32 txfe:1;
        T_UINT32 reserved:24;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_FR_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_ibrd_reg
    {
        T_UINT32 ibrd:16;
        T_UINT32 reserved:16;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_IBRD_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_fbrd_reg
    {
        T_UINT32 fbrd:6;
        T_UINT32 reserved:26;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_FBRD_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_lcrh_reg
    {
        T_UINT32 brk:1;
        T_UINT32 pen:1;
        T_UINT32 eps:1;
        T_UINT32 stp2:1;
        T_UINT32 fen:1;
        T_UINT32 wlen:2;
        T_UINT32 sps:1;
        T_UINT32 reserved:24;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_LCRH_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_cr_reg
    {
        T_UINT32 uarten:1;
        T_UINT32 reserved1:6;
        T_UINT32 lbe:1;
        T_UINT32 txe:1;
        T_UINT32 rxe:1;
        T_UINT32 reserved2:1;
        T_UINT32 rts:1;
        T_UINT32 reserved3:2;
        T_UINT32 rtsen:1;
        T_UINT32 ctsen:1;
        T_UINT32 reserved:16;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_CR_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_ifls_reg
    {
        T_UINT32 txiflsel:3;
        T_UINT32 rxiflsel:3;
        T_UINT32 reserved:26;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_IFLS_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_imsc_reg
    {
        T_UINT32 reserved0:1;
        T_UINT32 ctsmim:1;
        T_UINT32 reserved1:2;
        T_UINT32 rxim:1;
        T_UINT32 txim:1;
        T_UINT32 rtim:1;
        T_UINT32 feim:1;
        T_UINT32 peim:1;
        T_UINT32 beim:1;
        T_UINT32 oeim:1;
        T_UINT32 reserved:21;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_IMSC_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_ris_reg
    {
        T_UINT32 rirmis:1;
        T_UINT32 ctsrmis:1;
        T_UINT32 dcdrmis:1;
        T_UINT32 dsrrmis:1;
        T_UINT32 rxris:1;
        T_UINT32 txris:1;
        T_UINT32 rtris:1;
        T_UINT32 feris:1;
        T_UINT32 peris:1;
        T_UINT32 beris:1;
        T_UINT32 oeris:1;
        T_UINT32 reserved:21;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_RIS_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_mis_reg
    {
        T_UINT32 rimmis:1;
        T_UINT32 ctsmmis:1;
        T_UINT32 dcdmmis:1;
        T_UINT32 dsrmmis:1;
        T_UINT32 rxmis:1;
        T_UINT32 txmis:1;
        T_UINT32 rtmis:1;
        T_UINT32 femis:1;
        T_UINT32 pemis:1;
        T_UINT32 bemis:1;
        T_UINT32 oemis:1;
        T_UINT32 reserved:21;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_MIS_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_icr_reg
    {
        T_UINT32 rimic:1;
        T_UINT32 ctsmic:1;
        T_UINT32 dcdmic:1;
        T_UINT32 dsrmic:1;
        T_UINT32 rxic:1;
        T_UINT32 txic:1;
        T_UINT32 rtic:1;
        T_UINT32 feic:1;
        T_UINT32 peic:1;
        T_UINT32 beic:1;
        T_UINT32 oeic:1;
        T_UINT32 reserved:21;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_ICR_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_itcr_reg
    {
        T_UINT32 itcr0:1;
        T_UINT32 itcr1:1;
        T_UINT32 reserved:30;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_ITCR_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_itip_reg
    {
        T_UINT32 itip0:1;
        T_UINT32 reserved0:2;
        T_UINT32 itip3:1;
        T_UINT32 reserved:28;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_ITIP_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_itop_reg
    {
        T_UINT32 itop0:1;
        T_UINT32 reserved0:2;
        T_UINT32 itip3:1;
        T_UINT32 reserved1:2;
        T_UINT32 itip6:1;
        T_UINT32 itip7:1;
        T_UINT32 itip8:1;
        T_UINT32 itip9:1;
        T_UINT32 itip10:1;
        T_UINT32 itip11:1;
        T_UINT32 reserved:20;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_ITOP_REG;

typedef union
{
    /* Invidual bits */
    struct __uart_tdr_reg
    {
        T_UINT32 tdr10_0:11;
        T_UINT32 reserved:21;
    }bits;
    /* All register */
    T_UINT32 all;

}T_UART_TDR_REG;

typedef struct uart
{
    T_UART_DATA_REG     dr;
    T_UART_RSRECR_REG   rsrecr;

    T_UINT32            reserved1[((0x18 - 0x04) / 4) - 1];             /* Used for the gap in reg address check datasheet. */

    T_UART_FR_REG       fr;

    T_UINT32            reserved2[((0x20 - 0x18) / 4) - 1];             /* Used for the gap in reg address check datasheet. */
    T_UINT32            ilpr;                                           /* No supported */

    T_UART_IBRD_REG     ibrd;
    T_UART_FBRD_REG     fbrd;
    T_UART_LCRH_REG     lcrh;
    T_UART_CR_REG       cr;
    T_UART_IFLS_REG     ifls;
    T_UART_IMSC_REG     imsc;
    T_UART_RIS_REG      ris;
    T_UART_MIS_REG      mis;
    T_UART_ICR_REG      icr;

    T_UINT32            dmacr;                                          /* Not supported */
    T_UINT32            reserved3[((0x80 - 0x48) / 4) - 1];             /* Used for the gap in reg address check datasheet. */

    T_UART_ITCR_REG     itcr;
    T_UART_ITIP_REG     itip;
    T_UART_ITOP_REG     itop;
    T_UART_TDR_REG      tdr;

}T_UART;

/**************************************************************************************************
 *          Module Private vars.
 **************************************************************************************************/
//volatile T_UART* uart_dev = (T_UART*)SOC_UART_ADDR;

/**************************************************************************************************
 *          Public function implementation
 **************************************************************************************************/

T_STATUS bcm283x_uart_init(T_ADDRESS dev, T_UINT64 clock_rate_hz, T_UINT32 baud_rate)
{
    T_STATUS ret = OK;
    volatile T_UART* uart_dev = (volatile T_UART*)dev;


    T_UINT32 int_part = clock_rate_hz / (16 * baud_rate);
    T_FLOAT frac_part = (((T_FLOAT)clock_rate_hz / (16.0f * (T_FLOAT)baud_rate)) - (T_FLOAT)int_part) * 64.0f + 0.5f;

    uart_dev->ibrd.bits.ibrd = int_part;
    uart_dev->fbrd.bits.fbrd = (T_UINT32)frac_part;

    /* Set FIFO trigger level */
    uart_dev->ifls.bits.rxiflsel = ZERO;

    /* Enable UART interrupts. */
    uart_dev->imsc.bits.rxim = ENABLE;

    /* Enable FIFOS and set data size for 8 bits. See page 184 ARM peripherals manual. */
    uart_dev->lcrh.bits.wlen = 3;
    //uart_dev->lcrh.bits.fen  = ENABLE;

    /* Enable UART for TX and RX */
    uart_dev->cr.bits.uarten = ENABLE;
    uart_dev->cr.bits.txe    = ENABLE;
    uart_dev->cr.bits.rxe    = ENABLE;

    return ret;
}

T_VOID bcm283x_uart_send_char(T_ADDRESS dev, T_CHAR c)
{
    volatile T_UART* uart_dev = (volatile T_UART*)dev;

    while ( ONE == uart_dev->fr.bits.txff );

    uart_dev->dr.bits.data = c;
}

T_CHAR bcm283x_uart_recv_char(T_ADDRESS dev)
{
    volatile T_UART* uart_dev = (volatile T_UART*)dev;

    while ( ONE == uart_dev->fr.bits.rxfe );

    return uart_dev->dr.bits.data;
}

T_VOID bcm283x_uart_send_string(T_ADDRESS dev, T_STRING str)
{
    volatile T_UART* uart_dev = (volatile T_UART*)dev;

    while( '\0' != *str ) {
        bcm283x_uart_send_char((T_ADDRESS)uart_dev, *str++);
    }
}

