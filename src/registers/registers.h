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

namespace Registers {

struct Efer {
    uint64_t syscall_enable : 1;
    uint64_t reserved : 7;
    uint64_t long_mode_enable : 1;
    uint64_t reserved2 : 1;
    uint64_t long_mode_active : 1;
    uint64_t execute_disable_bit_enable : 1;
    uint64_t reserved3 : 52;
};

struct Rflags {
    uint64_t carry : 1;
    uint64_t reserved : 1;
    uint64_t parity : 1;
    uint64_t reserved2 : 1;
    uint64_t auxiliary : 1;
    uint64_t reserved3 : 1;
    uint64_t zero : 1;
    uint64_t sign : 1;
    uint64_t trap : 1;
    uint64_t interrupt : 1;
    uint64_t direction : 1;
    uint64_t overflow : 1;
    uint64_t io_privilege_level : 2;
    uint64_t nested_task : 1;
    uint64_t reserved4 : 1;
    uint64_t resume : 1;
    uint64_t virtual_8086_mode : 1;
    uint64_t alignment_check : 1;
    uint64_t virtual_interrupt : 1;
    uint64_t virtual_interrupt_pending : 1;
    uint64_t id : 1;
    uint64_t reserved5 : 42;
};

struct Cr0 {
    uint64_t protection_enabled : 1;
    uint64_t monitor_coprocessor : 1;
    uint64_t emulation : 1;
    uint64_t task_switched : 1;
    uint64_t extension_type : 1; // read only
    uint64_t numeric_error : 1;
    uint64_t reserved : 10;
    uint64_t write_protect : 1;
    uint64_t reserved2 : 1;
    uint64_t alignment_mask : 1;
    uint64_t reserved3 : 10;
    uint64_t not_writethrough : 1;
    uint64_t cache_disable : 1;
    uint64_t paging : 1;
    uint64_t reserved4 : 32;
};

struct Cr2 {
    uint64_t page_fault_linear_address;
};

struct Cr3 {
    uint64_t reserved : 3;
    uint64_t page_level_write_through : 1;
    uint64_t page_level_cache_disable : 1;
    uint64_t reserved2 : 7;
    uint64_t page_map_level_4_table_base_address : 40;
    uint64_t reserved3 : 12;
};

struct Cr4 {
    uint64_t virtual_8086_mode_extensions : 1;
    uint64_t protected_mode_virtual_interrupts : 1;
    uint64_t time_stamp_disable : 1;
    uint64_t debugging_extensions : 1;
    uint64_t page_size_extensions : 1;
    uint64_t physical_address_extension : 1;
    uint64_t machine_check_enable : 1;
    uint64_t page_global_enable : 1;
    uint64_t performance_monitoring_counter_enable : 1;
    uint64_t operating_system_fxsave_fxrstor_support : 1;
    uint64_t operating_system_unmasked_simd_exceptions_support : 1;
    uint64_t reserved : 2;
    uint64_t vmx_enable : 1;
    uint64_t smx_enable : 1;
    uint64_t reserved2 : 1;
    uint64_t fsgsbase_enable : 1;
    uint64_t pcid_enable : 1;
    uint64_t osxsave : 1;
    uint64_t reserved3 : 1;
    uint64_t smep_enable : 1;
    uint64_t smap_enable : 1;
    uint64_t reserved4 : 42;
};

struct XCR0 {
    uint64_t x87_state : 1; // must be 1
    uint64_t sse_state : 1;
    uint64_t avx_state : 1;
    uint64_t reserved : 61;
};

} // end namespace Registers
