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
 * @brief   - Bootloader board hw initialization.
 * @author  - tvasconcelos
 * @date    - 2020-03-05
 * @update  -
 *
 */

#include "types.h"
#include "board_periphmap.h"
#include "bcm283x_gpio.h"
#include "bcm283x_uart.h"
#include "bcm283x_gpu_mailbox.h"
#include "bcm283x_clocks.h"

#include "bcm283x_watchdog.h"

#include "kprint.h"
#include "entry.h"

/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/

T_VOID gpio_init();
T_VOID bus_init();
T_VOID show_bootloader_splash();

extern T_UINT32 __stack_pointer__;

/**************************************************************************************************
 *          Public functions implementation
 **************************************************************************************************/

/* TODO: Because the UART now needs the base address this function is a wrapper for now. Need to be rethinked later */
T_VOID ll_print(T_STRING str)
{
    bcm283x_uart_send_string(SOC_UART_ADDR, str);
}

T_VOID board_init()
{
    /* Initialize the gpu mailbox to retrieve the UART Clock */
    bcm283x_gpu_mailbox_init(SOC_GPU_MAILBOX_ADDR);

    /* Initialize the GPIO with the correct function */
    gpio_init();

    /* Initialize the communication buses */
    bus_init();

    /* Initialize kprint */
    kprint_init(ll_print);

    /* Display bootloader splash screen */
    show_bootloader_splash();

    /* Jump to bootloader code */
    bootloader_entry();

}

/**************************************************************************************************
 *          Private functions implementation
 **************************************************************************************************/

T_VOID gpio_init()
{
    /* Set GPIO pins to correct function for UART */
        bcm283x_gpio_set_function(SOC_GPIO_ADDR, UART_TX_GPIO, GPIO_ALT0);
        bcm283x_gpio_set_function(SOC_GPIO_ADDR, UART_RX_GPIO, GPIO_ALT0);
        /* Remove pull/up downs. */
        bcm283x_gpio_set_pull_up_down(SOC_GPIO_ADDR, UART_TX_GPIO, GPIO_PULL_UP_DOWN_DISABLE);
        bcm283x_gpio_set_pull_up_down(SOC_GPIO_ADDR, UART_RX_GPIO, GPIO_PULL_UP_DOWN_DISABLE);
}

T_VOID bus_init()
{
    T_UINT64 uart_clock_hz = bcm283x_get_clock_rate(E_CLOCK_UART);

    bcm283x_uart_init(SOC_UART_ADDR, uart_clock_hz, 115200);
}

static T_VOID clear_screen()
{
    kputs("\033[2J");
    kputs("\033[H");
}

T_VOID show_bootloader_splash()
{
    clear_screen();

    kputs(" __  _                   _            _ _             ___    ___  ___  _____ \n\r");
    kputs("/ _\\(_)_ __   __ _ _   _| | __ _ _ __(_) |_ _   _    / __\\  /___\\/___\\/__   \\\n\r");
    kputs("\\ \\ | | '_ \\ / _` | | | | |/ _` | '__| | __| | | |  /__\\// //  ///  //  / /\\/\n\r");
    kputs("_\\ \\| | | | | (_| | |_| | | (_| | |  | | |_| |_| | / \\/  \\/ \\_// \\_//  / /   \n\r");
    kputs("\\__/|_|_| |_|\\__, |\\__,_|_|\\__,_|_|  |_|\\__|\\__, | \\_____/\\___/\\___/   \\/    \n\r");
    kputs("             |___/                          |___/                            \n\r");
    kputs("          Bootloader for RPI4!!!\n\r");
    kputs("\n\r");

    kputs("***************** CLOCKS *****************\n\n\r");
    kprint("EMMC  : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_EMMC));
    kprint("UART  : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_UART));
    kprint("ARM   : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_ARM));
    kprint("CORE  : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_CORE));
    kprint("V3D   : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_V3D));
    kprint("H264  : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_H264));
    kprint("ISP   : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_ISP));
    kprint("SRAM  : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_SDRAM));
    kprint("PIXEL : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_PIXEL));
    kprint("PWM   : %dhz\n\r", bcm283x_get_clock_rate(E_CLOCK_PWM));
    kputs("\n\r******************************************\n\n\r");

    kprint("Current EL = %d\n\r", armv8_aarch64_get_exception_level());
}
