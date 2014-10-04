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

#include "segmentation/idt.h"

#include "segmentation/structs.h"
#include "interrupts/interrupts.h"
#include "segmentation/gdt.h"
#include "lib/util.h"
#include "asm/asm.h"

namespace
{

InterruptAndTrapGateDescriptor idt[256] = {};

InterruptAndTrapGateDescriptor make_intr_gate(void (*func)())
{
    auto x = reinterpret_cast<uint64_t>(func);

    return InterruptAndTrapGateDescriptor{
        .target_offset_15_0 = x & 0xffff,
        .target_selector = Segmentation::CS_SELECTOR_KERNEL,
        .ist = 0,
        .type = static_cast<uint8_t>(
            to_underlying_type(SystemSegmentDescriptorTypes::INTERRUPT_GATE)),
        .zero = 0,
        .descriptor_privilege_level =
            static_cast<uint8_t>(to_underlying_type(PrivilegeLevel::KERNEL)),
        .present = 1,
        .target_offset_31_16 = (x >> 16) & 0xffff,
        .target_offset_63_32 = (x >> 32) & 0xffffffff
    };
}
}

void Segmentation::setup_idt()
{
    idt[0] = make_intr_gate(intr_div_by_zero);
    idt[1] = make_intr_gate(intr_debug);
    idt[2] = make_intr_gate(intr_nmi);
    idt[3] = make_intr_gate(intr_breakpoint);
    idt[4] = make_intr_gate(intr_overflow);
    idt[5] = make_intr_gate(intr_bound_range);
    idt[6] = make_intr_gate(intr_invalid_opcode);
    idt[7] = make_intr_gate(intr_device_not_available);
    idt[8] = make_intr_gate(intr_double_fault);
    idt[10] = make_intr_gate(intr_invalid_tss);
    idt[11] = make_intr_gate(intr_segment_not_present);
    idt[12] = make_intr_gate(intr_stack);
    idt[13] = make_intr_gate(intr_general_protection);
    idt[14] = make_intr_gate(intr_page_fault);
    idt[16] = make_intr_gate(intr_x87_floating_point);
    idt[16] = make_intr_gate(intr_alignment_check);
    idt[18] = make_intr_gate(intr_machine_check);
    idt[19] = make_intr_gate(intr_simd_floating_point);

    DescriptorTableRegister dtr = { .limit = sizeof(idt) - 1,
                                    .base_address =
                                        reinterpret_cast<uint64_t>(&idt) };

    Asm::lidt(dtr);
}
