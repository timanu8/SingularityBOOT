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
 * @brief - iHex format parser.
 * @date  - 05-03-2020
 *
 */

#include "parse_ihex.h"
#include "hal.h"
#include "kprint.h"

extern void PUT8 ( unsigned int, unsigned int );
extern void PUT32 ( unsigned int, unsigned int );

/* GLOBAL VARIABLE TO SHARE THE START EXECUTION ADDRESS */
volatile T_UINT32 execution_start_addr = 0x00;

volatile T_CHAR c = '\0';
volatile T_UINT8 check_sum;
volatile T_UINT32 extended_linear_address = 0x00;

T_VOID write_byte_to_mem(T_UINT8* addr, T_UINT8 byte)
{
    *addr = byte;
}

T_CHAR __get_hex_char_from_value(T_UINT32 num)
{
    T_CHAR ret = '0';

    num &= 0x0F;

    if( 9 >= num ) {
        ret = num + '0';
    }
    else {
        ret = num - 10 + 'A';
    }

    return ret;
}


PRIVATE T_INT64 __get_value_from_hex_char(T_CHAR c)
{
    T_INT64 ret = ZERO;

    if( ('0' <= c) && ('9' >= c) ) {
        ret = (T_INT64)(c - '0');
    }
    else if( ('A' <= c) && ('F' >= c) ) {
        ret = (T_INT64)(c - 'A' + 10);
    }
    else if( ('a' <= c) && ('f' >= c) ) {
        ret = (T_INT64)(c - 'a' + 10);
    }

    return ret;
}

T_VOID parse_ihex_file()
{
    T_CHAR buffer[128];
    T_CHAR* ptr= buffer;

    extended_linear_address = 0x00;
    execution_start_addr = 0x00;

    kputs("Waiting iHex file... \n\r>\n\r");

    while(1)
    {
        /* Ignore all chars until find a start one */
        do
        {
            c = hal_get_char();
        }while(c != ':');

        /* For dbg */
        ptr= buffer;
        *ptr++ = ':';

        /* Initialize the check sum calculation variable */
        check_sum = 0x00;

        /* Parse the byte count param */
        T_UINT8 byte_count = ZERO;
        *ptr++ = c = hal_get_char();
        byte_count |= (__get_value_from_hex_char(c) << 4);
        *ptr++ = c = hal_get_char();
        byte_count |= (__get_value_from_hex_char(c) << 0);
        /* Update checksum */
        check_sum += byte_count;

        /* Parse the address param */
        T_UINT16 target_address = ZERO;
        *ptr++ = c = hal_get_char();
        target_address |= (__get_value_from_hex_char(c) << 12);
        *ptr++ = c = hal_get_char();
        target_address |= (__get_value_from_hex_char(c) << 8);
        *ptr++ = c = hal_get_char();
        target_address |= (__get_value_from_hex_char(c) << 4);
        *ptr++ = c = hal_get_char();
        target_address |= (__get_value_from_hex_char(c) << 0);
        /* Update checksum */
        check_sum += ((target_address >> 8) & 0x00FF);          /* Update with the high byte */
        check_sum += (target_address & 0x00FF);                 /* Update with the lower byte */

        /* Parse the cmd code param */
        T_UINT8 cmd_code = ZERO;
        *ptr++ = c = hal_get_char();
        cmd_code |= (__get_value_from_hex_char(c) << 4);
        *ptr++ = c = hal_get_char();
        cmd_code |= (__get_value_from_hex_char(c) << 0);
        /* Update checksum */
        check_sum += cmd_code;

        /* Execute according to the code received */
        switch(cmd_code)
        {
            case 0:
            {
                T_UINT8 new_byte = 0x00;
                T_UINT32 addr = extended_linear_address + (T_UINT32)target_address;

                for(int i = 0; i < byte_count; i++)
                {
                    new_byte = 0x00;
                    *ptr++ = c = hal_get_char();
                    new_byte |= (__get_value_from_hex_char(c) << 4);
                    *ptr++ = c = hal_get_char();
                    new_byte |= (__get_value_from_hex_char(c) << 0);
                    /* Update checksum */
                    check_sum += new_byte;

                    write_byte_to_mem((T_UINT8*)addr, new_byte);
                    addr++;
                }

            }
            break;
            case 1: kputs("End of file detected \n\r"); return; break;
            case 2:
            {
                T_UINT16 new_base_addr = 0x00;
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 12);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 8);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 0);
                /* Update checksum */
                check_sum += ((new_base_addr >> 8) & 0x00FF);          /* Update with the high byte */
                check_sum += (new_base_addr & 0x00FF);                 /* Update with the lower byte */

                /* Update the global variable */
                extended_linear_address = new_base_addr;
                extended_linear_address = (extended_linear_address << 4);

                break;
            }
            case 3:
            {
                execution_start_addr = 0x00;

                T_UINT8 byte = 0x00;
                T_UINT16 CS = 0x00;
                T_UINT16 IP = 0x00;

                /* CS High part */
                *ptr++ = c = hal_get_char();
                byte = (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                byte |= (__get_value_from_hex_char(c) << 0);

                CS = byte;
                CS = (CS << 8);

                /* Update checksum */
                check_sum += byte;

                /* CS Low part */
                *ptr++ = c = hal_get_char();
                byte = (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                byte |= (__get_value_from_hex_char(c) << 0);

                CS |= byte;

                /* Update checksum */
                check_sum += byte;

                /* IP High part */
                *ptr++ = c = hal_get_char();
                byte = (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                byte |= (__get_value_from_hex_char(c) << 0);

                IP = byte;
                IP = (IP << 8);

                /* Update checksum */
                check_sum += byte;

                /* IP Low part */
                *ptr++ = c = hal_get_char();
                byte = (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                byte |= (__get_value_from_hex_char(c) << 0);

                IP |= byte;

                /* Update checksum */
                check_sum += byte;

                /* Calculate the entry address */
                execution_start_addr = 0x10 * CS +IP;

                break;
            }
            case 4:
            {
                T_UINT16 new_base_addr = 0x00;
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 12);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 8);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 4);
                *ptr++ = c = hal_get_char();
                new_base_addr |= (__get_value_from_hex_char(c) << 0);
                /* Update checksum */
                check_sum += ((new_base_addr >> 8) & 0x00FF);          /* Update with the high byte */
                check_sum += (new_base_addr & 0x00FF);                 /* Update with the lower byte */

                /* Update the global variable */
                extended_linear_address = new_base_addr;
                extended_linear_address = (extended_linear_address << 16);

                break;
            }
                case 5:
                {
                    T_UINT8 byte = 0x00;
                    T_UINT32 EIP = 0x00;

                    *ptr++ = c = hal_get_char();
                    byte = (__get_value_from_hex_char(c) << 4);
                    *ptr++ = c = hal_get_char();
                    byte |= (__get_value_from_hex_char(c) << 0);

                    EIP |= ((T_UINT32)byte << 24);

                    /* Update checksum */
                    check_sum += byte;

                    *ptr++ = c = hal_get_char();
                    byte = (__get_value_from_hex_char(c) << 4);
                    *ptr++ = c = hal_get_char();
                    byte |= (__get_value_from_hex_char(c) << 0);

                    EIP |= ((T_UINT32)byte << 16);

                    /* Update checksum */
                    check_sum += byte;

                    *ptr++ = c = hal_get_char();
                    byte = (__get_value_from_hex_char(c) << 4);
                    *ptr++ = c = hal_get_char();
                    byte |= (__get_value_from_hex_char(c) << 0);

                    EIP |= ((T_UINT32)byte << 8);

                    /* Update checksum */
                    check_sum += byte;

                    *ptr++ = c = hal_get_char();
                    byte = (__get_value_from_hex_char(c) << 4);
                    *ptr++ = c = hal_get_char();
                    byte |= (__get_value_from_hex_char(c) << 0);

                    EIP |= ((T_UINT32)byte << 0);

                    /* Update checksum */
                    check_sum += byte;

                    /* Calculate the entry address */
                    execution_start_addr = EIP;

                }
                break;
            default:
                    kputs("Problem with the received data. No valid command detected \n\r");
                    *ptr = '\0';
                    kputs(buffer);
                break;
        }

        /* Finish calculation of our checksum with the two complement */
        check_sum ^= 0xFF;
        check_sum++;


        /* Parse received checksum */
        T_UINT8 rcv_check_sum = 0x00;
        *ptr++ = c = hal_get_char();
        rcv_check_sum |= (__get_value_from_hex_char(c) << 4);
        *ptr++ = c = hal_get_char();
        rcv_check_sum |= (__get_value_from_hex_char(c) << 0);

        /* compare the 2 */
        if ( check_sum != rcv_check_sum )
        {
            *ptr = '\0';
            kputs(buffer);
            kputs("Problem with the received data. Checksum error detected \n\r");
            kprint("calculated %x   rcv %x\n\r", check_sum, rcv_check_sum);
            kprint("execution_start_addr = 0x%x\n\r", execution_start_addr);
        }
    }
}
