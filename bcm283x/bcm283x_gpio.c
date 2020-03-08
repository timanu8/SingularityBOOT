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
 * @brief - bcm2837 gpio controller implementation file.
 * @date  - 27-07-2020
 *
 */

#include "types.h"
#include "values.h"
#include "error.h"
#include "bcm283x_gpio.h"

/**************************************************************************************************
 *          Driver defines
 **************************************************************************************************/


/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

T_VOID dummy_delay(T_UINT32 inst);

/**************************************************************************************************
 *          Driver structures
 **************************************************************************************************/

typedef union
{
    /* Invidual bits */
    struct __gpio_bits
    {
        T_UINT32 bit_0:1;
        T_UINT32 bit_1:1;
        T_UINT32 bit_2:1;
        T_UINT32 bit_3:1;
        T_UINT32 bit_4:1;
        T_UINT32 bit_5:1;
        T_UINT32 bit_6:1;
        T_UINT32 bit_7:1;
        T_UINT32 bit_8:1;
        T_UINT32 bit_9:1;
        T_UINT32 bit_10:1;
        T_UINT32 bit_11:1;
        T_UINT32 bit_12:1;
        T_UINT32 bit_13:1;
        T_UINT32 bit_14:1;
        T_UINT32 bit_15:1;
        T_UINT32 bit_16:1;
        T_UINT32 bit_17:1;
        T_UINT32 bit_18:1;
        T_UINT32 bit_19:1;
        T_UINT32 bit_20:1;
        T_UINT32 bit_21:1;
        T_UINT32 bit_22:1;
        T_UINT32 bit_23:1;
        T_UINT32 bit_24:1;
        T_UINT32 bit_25:1;
        T_UINT32 bit_26:1;
        T_UINT32 bit_27:1;
        T_UINT32 bit_28:1;
        T_UINT32 bit_29:1;
        T_UINT32 bit_30:1;
        T_UINT32 bit_31:1;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_BITS;


typedef union
{
    /* Invidual bits */
    struct __gpio_fsel0
    {
        T_UINT32 FSEL0:3;
        T_UINT32 FSEL1:3;
        T_UINT32 FSEL2:3;
        T_UINT32 FSEL3:3;
        T_UINT32 FSEL4:3;
        T_UINT32 FSEL5:3;
        T_UINT32 FSEL6:3;
        T_UINT32 FSEL7:3;
        T_UINT32 FSEL8:3;
        T_UINT32 FSEL9:3;
        T_UINT32 reserved:2;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL0;

typedef union
{
    /* Invidual bits */
    struct __gpio_fsel1
    {
        T_UINT32 FSEL10:3;
        T_UINT32 FSEL11:3;
        T_UINT32 FSEL12:3;
        T_UINT32 FSEL13:3;
        T_UINT32 FSEL14:3;
        T_UINT32 FSEL15:3;
        T_UINT32 FSEL16:3;
        T_UINT32 FSEL17:3;
        T_UINT32 FSEL18:3;
        T_UINT32 FSEL19:3;
        T_UINT32 reserved:2;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL1;

typedef union
{
    /* Invidual bits */
    struct __gpio_fsel2
    {
        T_UINT32 FSEL20:3;
        T_UINT32 FSEL21:3;
        T_UINT32 FSEL22:3;
        T_UINT32 FSEL23:3;
        T_UINT32 FSEL24:3;
        T_UINT32 FSEL25:3;
        T_UINT32 FSEL26:3;
        T_UINT32 FSEL27:3;
        T_UINT32 FSEL28:3;
        T_UINT32 FSEL29:3;
        T_UINT32 reserved:2;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL2;

typedef union
{
    /* Invidual bits */
    struct __gpio_fsel3
    {
        T_UINT32 FSEL30:3;
        T_UINT32 FSEL31:3;
        T_UINT32 FSEL32:3;
        T_UINT32 FSEL33:3;
        T_UINT32 FSEL34:3;
        T_UINT32 FSEL35:3;
        T_UINT32 FSEL36:3;
        T_UINT32 FSEL37:3;
        T_UINT32 FSEL38:3;
        T_UINT32 FSEL39:3;
        T_UINT32 reserved:2;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL3;

typedef union
{
    /* Invidual bits */
    struct __gpio_fsel4
    {
        T_UINT32 FSEL40:3;
        T_UINT32 FSEL41:3;
        T_UINT32 FSEL42:3;
        T_UINT32 FSEL43:3;
        T_UINT32 FSEL44:3;
        T_UINT32 FSEL45:3;
        T_UINT32 FSEL46:3;
        T_UINT32 FSEL47:3;
        T_UINT32 FSEL48:3;
        T_UINT32 FSEL49:3;
        T_UINT32 reserved:2;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL4;

typedef union
{
    /* Invidual bits */
    struct __gpio_fsel5
    {
        T_UINT32 FSEL50:3;
        T_UINT32 FSEL51:3;
        T_UINT32 FSEL52:3;
        T_UINT32 FSEL53:3;
        T_UINT32 reserved:20;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_FSEL5;

typedef union
{
    /* Invidual bits */
    struct __gpio_gppud
    {
        T_UINT32 PUD:2;
        T_UINT32 reserved:30;
    }bits;
    /* All register */
    T_UINT32 all;

}T_GPIO_GPPUD;


typedef struct gpio
{
    T_GPIO_FSEL0 GPFSEL0;
    T_GPIO_FSEL1 GPFSEL1;
    T_GPIO_FSEL2 GPFSEL2;
    T_GPIO_FSEL3 GPFSEL3;
    T_GPIO_FSEL4 GPFSEL4;
    T_GPIO_FSEL5 GPFSEL5;
    T_GPIO_BITS reserved0;
    T_GPIO_BITS GPSET0;
    T_GPIO_BITS GPSET1;
    T_GPIO_BITS reserved1;
    T_GPIO_BITS GPCLR0;
    T_GPIO_BITS GPCLR1;
    T_GPIO_BITS reserved2;
    T_GPIO_BITS GPLEV0;
    T_GPIO_BITS GPLEV1;
    T_GPIO_BITS reserved3;
    T_GPIO_BITS GPEDS0;
    T_GPIO_BITS GPEDS1;
    T_GPIO_BITS reserved4;
    T_GPIO_BITS GPREN0;
    T_GPIO_BITS GPREN1;
    T_GPIO_BITS reserved5;
    T_GPIO_BITS GPFEN0;
    T_GPIO_BITS GPFEN1;
    T_GPIO_BITS reserved6;
    T_GPIO_BITS GPHEN0;
    T_GPIO_BITS GPHEN1;
    T_GPIO_BITS reserved7;
    T_GPIO_BITS GPLEN0;
    T_GPIO_BITS GPLEN1;
    T_GPIO_BITS reserved8;
    T_GPIO_BITS GPAREN0;
    T_GPIO_BITS GPAREN1;
    T_GPIO_BITS reserved9;
    T_GPIO_BITS GPAFEN0;
    T_GPIO_BITS GPAFEN1;
    T_GPIO_BITS reserved10;
    T_GPIO_GPPUD GPPUD;
    T_GPIO_BITS GPPUDCLK0;
    T_GPIO_BITS GPPUDCLK1;

}T_GPIO;


/**************************************************************************************************
 *          Driver Private variables
 **************************************************************************************************/

/**************************************************************************************************
 *          Public function implementation
 **************************************************************************************************/

T_VOID bcm283x_gpio_set_function(T_ADDRESS dev, T_UINT32 pin, T_UINT32 function)
{
    volatile T_GPIO* gpio_dev = (volatile T_GPIO*)dev;

    switch ( pin ) {

    case 0: gpio_dev->GPFSEL0.bits.FSEL0 = function; break;
    case 1: gpio_dev->GPFSEL0.bits.FSEL1 = function; break;
    case 2: gpio_dev->GPFSEL0.bits.FSEL2 = function; break;
    case 3: gpio_dev->GPFSEL0.bits.FSEL3 = function; break;
    case 4: gpio_dev->GPFSEL0.bits.FSEL4 = function; break;
    case 5: gpio_dev->GPFSEL0.bits.FSEL5 = function; break;
    case 6: gpio_dev->GPFSEL0.bits.FSEL6 = function; break;
    case 7: gpio_dev->GPFSEL0.bits.FSEL7 = function; break;
    case 8: gpio_dev->GPFSEL0.bits.FSEL8 = function; break;
    case 9: gpio_dev->GPFSEL0.bits.FSEL9 = function; break;

    case 10: gpio_dev->GPFSEL1.bits.FSEL10 = function; break;
    case 11: gpio_dev->GPFSEL1.bits.FSEL11 = function; break;
    case 12: gpio_dev->GPFSEL1.bits.FSEL12 = function; break;
    case 13: gpio_dev->GPFSEL1.bits.FSEL13 = function; break;
    case 14: gpio_dev->GPFSEL1.bits.FSEL14 = function; break;
    case 15: gpio_dev->GPFSEL1.bits.FSEL15 = function; break;
    case 16: gpio_dev->GPFSEL1.bits.FSEL16 = function; break;
    case 17: gpio_dev->GPFSEL1.bits.FSEL17 = function; break;
    case 18: gpio_dev->GPFSEL1.bits.FSEL18 = function; break;
    case 19: gpio_dev->GPFSEL1.bits.FSEL19 = function; break;

    case 20: gpio_dev->GPFSEL2.bits.FSEL20 = function; break;
    case 21: gpio_dev->GPFSEL2.bits.FSEL21 = function; break;
    case 22: gpio_dev->GPFSEL2.bits.FSEL22 = function; break;
    case 23: gpio_dev->GPFSEL2.bits.FSEL23 = function; break;
    case 24: gpio_dev->GPFSEL2.bits.FSEL24 = function; break;
    case 25: gpio_dev->GPFSEL2.bits.FSEL25 = function; break;
    case 26: gpio_dev->GPFSEL2.bits.FSEL26 = function; break;
    case 27: gpio_dev->GPFSEL2.bits.FSEL27 = function; break;
    case 28: gpio_dev->GPFSEL2.bits.FSEL28 = function; break;
    case 29: gpio_dev->GPFSEL2.bits.FSEL29 = function; break;

    case 30: gpio_dev->GPFSEL3.bits.FSEL30 = function; break;
    case 31: gpio_dev->GPFSEL3.bits.FSEL31 = function; break;
    case 32: gpio_dev->GPFSEL3.bits.FSEL32 = function; break;
    case 33: gpio_dev->GPFSEL3.bits.FSEL33 = function; break;
    case 34: gpio_dev->GPFSEL3.bits.FSEL34 = function; break;
    case 35: gpio_dev->GPFSEL3.bits.FSEL35 = function; break;
    case 36: gpio_dev->GPFSEL3.bits.FSEL36 = function; break;
    case 37: gpio_dev->GPFSEL3.bits.FSEL37 = function; break;
    case 38: gpio_dev->GPFSEL3.bits.FSEL38 = function; break;
    case 39: gpio_dev->GPFSEL3.bits.FSEL39 = function; break;

    case 40: gpio_dev->GPFSEL4.bits.FSEL40 = function; break;
    case 41: gpio_dev->GPFSEL4.bits.FSEL41 = function; break;
    case 42: gpio_dev->GPFSEL4.bits.FSEL42 = function; break;
    case 43: gpio_dev->GPFSEL4.bits.FSEL43 = function; break;
    case 44: gpio_dev->GPFSEL4.bits.FSEL44 = function; break;
    case 45: gpio_dev->GPFSEL4.bits.FSEL45 = function; break;
    case 46: gpio_dev->GPFSEL4.bits.FSEL46 = function; break;
    case 47: gpio_dev->GPFSEL4.bits.FSEL47 = function; break;
    case 48: gpio_dev->GPFSEL4.bits.FSEL48 = function; break;
    case 49: gpio_dev->GPFSEL4.bits.FSEL49 = function; break;

    case 50: gpio_dev->GPFSEL5.bits.FSEL50 = function; break;
    case 51: gpio_dev->GPFSEL5.bits.FSEL51 = function; break;
    case 52: gpio_dev->GPFSEL5.bits.FSEL52 = function; break;
    case 53: gpio_dev->GPFSEL5.bits.FSEL53 = function; break;
    }
}

T_VOID bcm283x_gpio_set_value(T_ADDRESS dev, T_UINT32 pin, T_UINT32 value)
{
    volatile T_GPIO* gpio_dev = (volatile T_GPIO*)dev;

    if ( GPIO_LOW == value ) {

        if ( 32 <= pin ) {

            pin -= 32;

            gpio_dev->GPCLR1.all |= (ONE << pin);
        }
        else {

            gpio_dev->GPCLR0.all |= (ONE << pin);
        }
    }
    else {

        if ( 32 <= pin ) {

            pin -= 32;

            gpio_dev->GPSET1.all |= (ONE << pin);
        }
        else {

            gpio_dev->GPSET0.all |= (ONE << pin);
        }
    }
}

T_VOID bcm283x_gpio_set_pull_up_down(T_ADDRESS dev, T_UINT32 pin, T_UINT32 value)
{
    volatile T_GPIO* gpio_dev = (volatile T_GPIO*)dev;

    gpio_dev->GPPUD.bits.PUD = value;

    /* Manual sugest 150 cycles delay. */
    dummy_delay(250);

    if ( 32 > pin ) {
        gpio_dev->GPPUDCLK0.all |= ( ONE << pin );
    }
    else {
        gpio_dev->GPPUDCLK1.all |= ( ONE << (pin - 32) );
    }

    dummy_delay(250);

    gpio_dev->GPPUDCLK0.all = ZERO;
    gpio_dev->GPPUDCLK1.all = ZERO;
}


/**************************************************************************************************
 *          Private function implementation
 **************************************************************************************************/

volatile T_UINT32 dummy_aux;

T_VOID dummy_delay(T_UINT32 inst)
{
    dummy_aux = inst;

    while ( ZERO < dummy_aux-- );
}

