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
 * @brief   - Bootloader entry point.
 * @author  - tvasconcelos
 * @date    - 2020-03-05
 * @update  -
 *
 */

/* To keep this in the first portion of the binary. */
.section ".text", "ax"

/* Make _start global. */
.globl _start
_start:

_core_check:
    /* Park secondary cores. And keep execution only with core 0 */
    mrs x0,mpidr_el1
    mov x1,#0xFF000000
    bic x0,x0,x1
    cbz x0,core_zero
    sub x1,x0,#1
    cbz x1,core_one
    sub x1,x0,#2
    cbz x1,core_two
    sub x1,x0,#3
    cbz x1,core_three

core_zero:
    /* set stack poiter */
    ldr x0, =__stack_pointer__
    mov sp, x0

    /* Jump to BSP main entry point */
    bl  board_init

loop: b loop

core_one:
    ldr x0, =__core_1_park_addr__
    mov x1, #0x00
    str x1, [x0]
core_one_loop:
    ldr x1, [x0]
    cbz x1, core_one_loop
    blr x1

core_two:
    ldr x0, =__core_2_park_addr__
    mov x1, #0x00
    str x1, [x0]
core_two_loop:
    ldr x1, [x0]
    cbz x1, core_two_loop
    blr x1

core_three:
    ldr x0, =__core_3_park_addr__
    mov x1, #0x00
    str x1, [x0]
core_three_loop:
    ldr x1, [x0]
    cbz x1, core_three_loop
    blr x1


.globl jump_to_entry_core_0
jump_to_entry_core_0:
    mov x3, x0
    ldr x0, =__core_1_park_addr__
    ldr x1, =__core_2_park_addr__
    ldr x2, =__core_3_park_addr__
    blr x3

.globl PUT8
PUT8:
  strb w1,[x0]
  ret
