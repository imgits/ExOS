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

#include "interrupts/interrupts.h"

#include "asm/asm.h"
#include "lib/printf.h"

#define SYSV_ABI __attribute__((sysv_abi))

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

extern "C" {

[[noreturn]] SYSV_ABI void
intr_div_by_zero_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Divide by zero!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_debug_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Debug!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_nmi_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: NMI"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_breakpoint_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Breakpoint!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_overflow_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Overflow!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_bound_range_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Bound Range!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_invalid_opcode_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Invalid Opcode!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_device_not_available_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Device not available!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_double_fault_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Double Fault!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_invalid_tss_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Invalid TSS!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_segment_not_present_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Segment Not Present!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_stack_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Stack!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_general_protection_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: General Protection!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_page_fault_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Page Fault!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_x87_floating_point_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: x87 Floating Point!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_alignment_check_cpp(const Interrupts::StackWithErrorCode *stack)
{
    (void)stack;
    printf("INTR: Alignment Check!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_machine_check_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: Machine Check!"_cts);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_simd_floating_point_cpp(const Interrupts::StackNoErrorCode *stack)
{
    (void)stack;
    printf("INTR: SIMD Floating Point!"_cts);
    Asm::hlt();
}

} // end extern "C"

#pragma clang diagnostic pop
