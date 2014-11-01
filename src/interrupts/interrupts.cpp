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
#include "lib/util.h"

#define SYSV_ABI __attribute__((sysv_abi))

namespace {

StringRef priv_to_string(uint8_t priv)
{
    switch (priv) {
    case to_underlying_type(Descriptors::PrivilegeLevel::KERNEL): return "Kernel"_s;
    case to_underlying_type(Descriptors::PrivilegeLevel::USER):   return "User"_s;
    default: assert(0 && "Invalid privilege level");
    }
}

StringRef ti_to_string(uint8_t ti)
{
    switch (ti) {
    case to_underlying_type(Descriptors::TableIndicator::GDT): return "GDT"_s;
    case to_underlying_type(Descriptors::TableIndicator::LDT): return "LDT"_s;
    default: assert(0 && "Invalid Table Indicator");
    }
}

void print_selector(Descriptors::SegmentSelector sel)
{
    printf("() ()[()]\n"_c, priv_to_string(sel.requestor_privilege_level),
           ti_to_string(sel.table_indicator), sel.selector_index / 2);
}

void print_stack(const Interrupts::StackNoErrorCode &stack)
{
    printf("RIP: 0x(016x)\n"_c, stack.return_rip);
    printf("CS: "_c);
    print_selector(stack.return_cs);
    printf("RFLAGS: 0x(016x)\n"_c, *reinterpret_cast<const uint64_t *>(&stack.rflags));
    printf("RSP: 0x(016x)\n"_c, stack.return_rsp);
    printf("SS: "_c);
    print_selector(stack.return_ss);
}

} // end anonymous namespace

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

extern "C" {

[[noreturn]] SYSV_ABI void
intr_div_by_zero_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Division by Zero\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_debug_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Debug\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_nmi_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: NMI\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_breakpoint_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Breakpoint\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_overflow_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Overflow\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_bound_range_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Bound Range\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_invalid_opcode_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Invalid Opcode\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_device_not_available_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Device not Available\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_double_fault_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Double Fault\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_invalid_tss_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Invalid TSS\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_segment_not_present_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Segment not Present\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_stack_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Stack\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_general_protection_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: General Protection\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_page_fault_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Page Fault\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_x87_floating_point_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: x87 Floating Point\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_alignment_check_cpp(const Interrupts::StackWithErrorCode *stack)
{
    printf("[INTERRUPT]: Alignment Check\n"_c);
    print_stack(stack->rest_of_stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_machine_check_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: Machine Check\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

[[noreturn]] SYSV_ABI void
intr_simd_floating_point_cpp(const Interrupts::StackNoErrorCode *stack)
{
    printf("[INTERRUPT]: SIMD Floating Point\n"_c);
    print_stack(*stack);
    Asm::hlt();
}

} // end extern "C"

#pragma clang diagnostic pop
