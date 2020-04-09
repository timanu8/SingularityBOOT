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
 * @brief - SOC peripheral mapping.
 * @date  - 27-02-2020
 *
 */

#ifndef __BOARD_PERIPHMAP_H__
#define __BOARD_PERIPHMAP_H__

#define BCM2711_TOTAL_CORES                 4

/* SOC devices address */
#define SOC_PERIPH_BASE_ADDR                 0xFE000000

#define SOC_SYS_TIMER_ADDR                  ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00003000))
#define SOC_DMA_ADDR                        ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00007000))
#define SOC_IRQ_CONTROLLER_ADDR             ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x0000B200))
#define SOC_ARM_TIMER                       ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x0000B400))
#define SOC_GPIO_ADDR                       ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00200000))
#define SOC_UART_ADDR                       ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00201000))
#define SOC_MINI_UART_ADDR                  ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00215000))
#define SOC_EMMC_ADDR                       ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00300000))
#define SOC_GPU_MAILBOX_ADDR                ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x0000B880))
#define SOC_WATCHDOG_ADDR                   ((T_ADDRESS)(SOC_PERIPH_BASE_ADDR + 0x00100000))

/* BCM2837 specific peripherals */
#define SOC_LOCAL_TIMER_CS                  (0x40000034)
#define SOC_LOCAL_IMER_IRQ_CR               (0x40000038)
#define SOC_LOCAL_TIMER_IRQ_ROUTE           (0x40000024)

/*
 * IRQ IDs Macros. Note: arm peripherals dont't have an ID on datasheet. The ID given is a trick to make
 * mask them in next register space.
 */
#define SOC_IRQ_AUX_PERIPHERAL              29              /* In RPI2/RPI3 aux periph have miniUART and 2 SPIs */
#define SOC_IRQ_I2C_SPI_SLAVE               43
#define SOC_IRQ_PWA0                        45
#define SOC_IRQ_PWA1                        46
#define SOC_IRQ_SMI                         48
#define SOC_IRQ_GPIO0                       49
#define SOC_IRQ_GPIO1                       50
#define SOC_IRQ_GPIO2                       51
#define SOC_IRQ_GPIO3                       52
#define SOC_IRQ_I2C                         53
#define SOC_IRQ_SPI                         54
#define SOC_IRQ_PCM                         55
#define SOC_IRQ_UART                        57
#define SOC_IRQ_ARM_TIMER                   64
#define SOC_IRQ_ARM_MAILBOX                 65
#define SOC_IRQ_ARM_DOORBELL0               66
#define SOC_IRQ_ARM_DOORBELL1               67
#define SOC_IRQ_GPU_HALTED0                 68
#define SOC_IRQ_GPU_HALTED1                 69
#define SOC_IRQ_ILLEGAL_ACCESS_TYPE1        70
#define SOC_IRQ_ILLEGAL_ACCESS_TYPE0        71
#define SOC_IRQ_CNTPSIRQ                    96
#define SOC_IRQ_CNTPNSIRQ                   97
#define SOC_IRQ_CNTHPIRQ                    98
#define SOC_IRQ_CNTVIRQ                     99
#define SOC_IRQ_MAILBOX0                    100
#define SOC_IRQ_MAILBOX1                    101
#define SOC_IRQ_MAILBOX2                    102
#define SOC_IRQ_MAILBOX3                    103
#define SOC_IRQ_GPU                         104
#define SOC_IRQ_PMU                         105
#define SOC_IRQ_AXI                         106
#define SOC_IRQ_LOCAL_TIMER                 107

#define SOC_IRQ_TOTAL                       108

/*
 * GPIO Mapping
 */
#define UART_TX_GPIO            14
#define UART_RX_GPIO            15

#endif /* __BOARD_PERIPHMAP_H__ */
