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
 * @brief - bcm2837 watchdog controller implementation file.
 * @date  - 28-02-2020
 *
 * This module is quite triky because someone reversed engineered this function from
 * the linux driver. There are no documentation about this one, thats why for now it
 * will not follow the device driver structure.
 *
 */

#include "types.h"
#include "values.h"
#include "error.h"
#include "board_periphmap.h"
#include "bcm283x_watchdog.h"

/**************************************************************************************************
 *          Driver defines
 **************************************************************************************************/

#define PM_BASE                     (SOC_PERIPH_BASE_ADDR + 0x100000) /* Power Management, Reset controller and Watchdog registers */
#define PM_RSTC                     (PM_BASE+0x1c)
#define PM_WDOG                     (PM_BASE+0x24)
#define PM_WDOG_RESET               0000000000
#define PM_PASSWORD                 0x5a000000
#define PM_WDOG_TIME_SET            0x000fffff
#define PM_RSTC_WRCFG_CLR           0xffffffcf
#define PM_RSTC_WRCFG_SET           0x00000030
#define PM_RSTC_WRCFG_FULL_RESET    0x00000020
#define PM_RSTC_RESET               0x00000102

#define WDOG_BASE_CLOCK             62500                   /* 62500Hz its the frequency used to calculate that 63 on start */

/**************************************************************************************************
 *          Private functions declaration
 **************************************************************************************************/


/**************************************************************************************************
 *          Driver structures
 **************************************************************************************************/


/**************************************************************************************************
 *          Driver Private variables
 **************************************************************************************************/

volatile T_UINT32* pm_rstc;
volatile T_UINT32* pm_wdog;

/**************************************************************************************************
 *          Public function implementation
 **************************************************************************************************/

T_VOID bcm283x_watchdog_init(T_ADDRESS dev)
{
//    pm_wdog = (T_UINT32*)((T_UINT32)dev + 0x1c);
//    pm_rstc = (T_UINT32*)((T_UINT32)dev + 0x24);
}

T_VOID bcm283x_watchdog_start(T_UINT32 msec)
{
    volatile T_UINT32* pm_rstc;
    volatile T_UINT32* pm_wdog;

    pm_wdog = (T_UINT32*)PM_WDOG;
    pm_rstc = (T_UINT32*)PM_RSTC;

    *pm_wdog = PM_PASSWORD | ((msec* 63) & PM_WDOG_TIME_SET); // watchdog timer = timer clock / 16; need password (31:16) + value (11:0)
    *pm_rstc = PM_PASSWORD | (*pm_rstc & PM_RSTC_WRCFG_CLR) | PM_RSTC_WRCFG_FULL_RESET;
}

T_VOID bcm283x_watchdog_stop()
{
    volatile T_UINT32* pm_wdog;
    volatile T_UINT32* pm_rstc;

    pm_wdog = (T_UINT32*)PM_WDOG;
    pm_rstc = (T_UINT32*)PM_RSTC;

    *pm_wdog = PM_PASSWORD | PM_RSTC_WRCFG_CLR;
    *pm_rstc = PM_PASSWORD | (*pm_rstc & PM_RSTC_WRCFG_CLR);
}

/**************************************************************************************************
 *          Private function implementation
 **************************************************************************************************/
