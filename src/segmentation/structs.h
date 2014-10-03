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

enum class TableIndicator
{
    GDT = 0,
    LDT = 1
};

enum class PrivilegeLevel
{
    KERNEL = 0,
    USER = 3
};

struct SegmentSelector
{
    uint16_t requestor_privilege_level : 2;
    uint16_t table_indicator : 1;
    uint16_t selector_index : 13;
};

struct DescriptorTableRegister
{
    uint16_t limit;
    uint64_t base_address __attribute__((packed));
};

struct CodeSegmentDescriptor
{
    uint64_t ignored : 42;
    uint64_t conforming : 1;
    uint64_t one : 1;
    uint64_t one2 : 1;
    uint64_t descriptor_privilege_level : 2;
    uint64_t present : 1;
    uint64_t ignored2 : 5;
    uint64_t long_attribute : 1;
    uint64_t default_operand_size : 1;
    uint64_t ignored3 : 9;
};

struct DataSegmentDescriptor
{
    uint64_t ignored : 43;
    uint64_t zero : 1;
    uint64_t one : 1;
    uint64_t ignored2 : 2;
    uint64_t present : 1;
    uint64_t ignored3 : 16;
};

enum class SystemSegmentDescriptorTypes
{
    LDT = 0x2,
    TSS_AVAILABLE = 0x9,
    TSS_BUSY = 0xa,
    CALL_GATE = 0xc,
    INTERRUPT_GATE = 0xe,
    TRAP_GATE = 0xf
};

struct SystemSegmentDescriptor
{
    uint64_t segment_limit_15_0 : 16;
    uint64_t base_address_23_0 : 24;
    uint64_t type : 4;
    uint64_t zero : 1;
    uint64_t descriptor_privilege_level : 2;
    uint64_t present : 1;
    uint64_t sement_limit_19_16 : 4;
    uint64_t avl : 1;
    uint64_t ignored : 2;
    uint64_t granularity : 1;
    uint64_t base_address_31_24 : 8;
    uint64_t base_adddress_32_63 : 32;
    uint64_t ignored2 : 8;
    uint64_t zero2 : 5;
    uint64_t ignored3 : 19;
};

struct CallGateDescriptor
{
    uint64_t target_offset_15_0 : 16;
    SegmentSelector target_selector;
    uint64_t ignored : 8;
    uint64_t type : 4;
    uint64_t zero : 1;
    uint64_t descriptor_privilege_level : 2;
    uint64_t present : 1;
    uint64_t target_offset_63_16 : 48;
    uint64_t ignored2 : 8;
    uint64_t zero2 : 5;
    uint64_t ignored3 : 19;
};

struct InterruptAndTrapGateDescriptor
{
    uint64_t target_offset_15_0;
    SegmentSelector target_selector;
    uint64_t ist : 3;
    uint64_t ignored : 5;
    uint64_t type : 4;
    uint64_t zero : 1;
    uint64_t descriptor_privilege_level : 2;
    uint64_t present : 1;
    uint64_t target_offset_63_16 : 48;
    uint64_t ignored2 : 32;
};
