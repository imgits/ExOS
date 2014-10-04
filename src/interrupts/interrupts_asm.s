/*
 * Copyright (c) 2014, Thorben Hasenpusch <t.hasenpusch@icloud.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* Interrupt handlers */

// DE - Divide-by-Zero Exception (Vector 0)
.globl _intr_div_by_zero
_intr_div_by_zero:
    movq %rsp, %rdi
    call _intr_div_by_zero_cpp
    iretq

// DB - Debug Exception (Vector 1)
.globl _intr_debug
_intr_debug:
    movq %rsp, %rdi
    call _intr_debug_cpp
    iretq

// NMI - Non-Maskable-Interrupt Exception (Vector 2)
.globl _intr_nmi
_intr_nmi:
    movq %rsp, %rdi
    call _intr_nmi_cpp
    iretq

// BP - Breakpoint Exception (Vector 3)
.globl _intr_breakpoint
_intr_breakpoint:
    movq %rsp, %rdi
    call _intr_breakpoint_cpp
    iretq

// OF - Overflow Exception (Vector 4)
.globl _intr_overflow
_intr_overflow:
    movq %rsp, %rdi
    call _intr_overflow_cpp
    iretq

// BR - Bound-Range Exception (Vector 5)
.globl _intr_bound_range
_intr_bound_range:
    movq %rsp, %rdi
    call _intr_bound_range_cpp
    iretq

// UD - Invalid-Opcode Exception (Vector 6)
.globl _intr_invalid_opcode
_intr_invalid_opcode:
    movq %rsp, %rdi
    call _intr_invalid_opcode_cpp
    iretq

// NM - Device-Not-Available Exception (Vector 7)
.globl _intr_device_not_available
_intr_device_not_available:
    movq %rsp, %rdi
    call _intr_device_not_available_cpp
    iretq

// DF - Double-Fault Exception (Vector 8)
.globl _intr_double_fault
_intr_double_fault:
    movq %rsp, %rdi
    call _intr_double_fault_cpp
    iretq

// TS - Invalid-TSS Exception (Vector 10)
.globl _intr_invalid_tss
_intr_invalid_tss:
    movq %rsp, %rdi
    call _intr_invalid_tss_cpp
    iretq

// NP - Segment-Not-Present Exception (Vector 11)
.globl _intr_segment_not_present
_intr_segment_not_present:
    movq %rsp, %rdi
    call _intr_segment_not_present_cpp
    iretq

// SS - Stack Exception (Vector 12)
.globl _intr_stack
_intr_stack:
    movq %rsp, %rdi
    call _intr_stack_cpp
    iretq

// GP - General-Protection Exception (Vector 13)
.globl _intr_general_protection
_intr_general_protection:
    movq %rsp, %rdi
    call _intr_general_protection_cpp
    iretq

// PF - Page Fault Exception (Vector 14)
.globl _intr_page_fault
_intr_page_fault:
    movq %rsp, %rdi
    call _intr_page_fault_cpp
    iretq

// MF - x87 Floating-Point Exception-Pending (Vector 16)
.globl _intr_x87_floating_point
_intr_x87_floating_point:
    movq %rsp, %rdi
    call _intr_x87_floating_point_cpp
    iretq

// AC - Alignment-Check Exception (Vector 17)
.globl _intr_alignment_check
_intr_alignment_check:
    movq %rsp, %rdi
    call _intr_alignment_check_cpp
    iretq

// MC - Machine-Check Exception (Vector 18)
.globl _intr_machine_check
_intr_machine_check:
    movq %rsp, %rdi
    call _intr_machine_check_cpp
    iretq

// XF - SIMD Floating-Point Exception (Vector 19)
.globl _intr_simd_floating_point
_intr_simd_floating_point:
    movq %rsp, %rdi
    call _intr_simd_floating_point_cpp
    iretq
