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

#pragma once

#include <cstdint>

#include "segmentation/structs.h"
#include "registers/registers.h"

namespace Interrupts
{

struct SelectorErrorCode
{
    uint32_t ext : 1;
    uint32_t idt : 1;
    uint32_t ti : 1;
    uint32_t selector_index : 13;
    uint32_t reserved : 16;
};

struct PageFaultErrorCode
{
    uint32_t p : 1;
    uint32_t rw : 1;
    uint32_t us : 1;
    uint32_t rsv : 1;
    uint32_t id : 1;
    uint32_t reserved : 27;
};

union ErrorCode
{
    SelectorErrorCode selector_error;
    PageFaultErrorCode page_fault_error;
};

struct Cr8
{
    uint64_t task_priority : 4;
    uint64_t reserved : 60;
};

struct StackNoErrorCode
{
    void *return_rip;
    SegmentSelector return_cs;
    uint8_t __pad[6];
    Registers::Rflags rflags;
    void *return_rsp;
    SegmentSelector return_ss;
    uint8_t __pad2[6];
};

struct StackWithErrorCode
{
    ErrorCode error_code;
    uint8_t __pad[4];
    StackNoErrorCode rest_of_stack;
};

} // end namespace Interrupts

extern "C" {

void intr_div_by_zero();
void intr_debug();
void intr_nmi();
void intr_breakpoint();
void intr_overflow();
void intr_bound_range();
void intr_invalid_opcode();
void intr_device_not_available();
void intr_double_fault();
void intr_invalid_tss();
void intr_segment_not_present();
void intr_stack();
void intr_general_protection();
void intr_page_fault();
void intr_x87_floating_point();
void intr_alignment_check();
void intr_machine_check();
void intr_simd_floating_point();

} // end extern "C"
