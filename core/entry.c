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
 * @brief - Bootloader entry.
 * @date  - 05-03-2020
 *
 */

#include "types.h"
#include "error.h"
#include "values.h"
#include "kprint.h"
#include "hal.h"
#include "parse_ihex.h"


extern volatile T_UINT32 execution_start_addr;

extern T_UINT32 __core_1_park_addr__;
extern T_UINT32 __core_2_park_addr__;
extern T_UINT32 __core_3_park_addr__;

T_VOID finalize_and_jump();



T_VOID bootloader_entry()
{
    parse_ihex_file();

    finalize_and_jump();
}

static T_VOID clear_screen()
{
    kputs("\033[2J");
    kputs("\033[H");
}

T_VOID finalize_and_jump()
{
    T_UINT8 c;

    /* Display the calculated code entry address */
    kprint("\n\n\rCode entry address 0x%x\n\r", execution_start_addr);

    kputs("Remain cores will park at:\n\r");
    kprint("     Core 1 : 0x%x  -> Register 0 hold this address\n\r", &__core_1_park_addr__);
    kprint("     Core 2 : 0x%x  -> Register 1 hold this address\n\r", &__core_2_park_addr__);
    kprint("     Core 3 : 0x%x  -> Register 2 hold this address\n\r", &__core_3_park_addr__);

    kputs("\n\n\rPress g or G to jump to your code.\n\r");
    kputs("         GOOD LUCK and GODSPEED\n\r");

    do
    {
        c = hal_get_char();
    }while (c != 'g' && c != 'G');

    clear_screen();

    /* Jump to the downloaded app */
    jump_to_entry_core_0(execution_start_addr);
}

