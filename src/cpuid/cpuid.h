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

#include "lib/array.h"

namespace Cpuid {

// Executes the cpuid instruction with the given register values.
void cpuid(std::uint32_t eax_in, std::uint32_t ebx_in, std::uint32_t &eax_out,
           std::uint32_t &ebx_out, std::uint32_t &ecx_out, std::uint32_t &edx_out);

// Returns the CPU vendor string (GenuineIntel, AuthenticAMD, etc...).
String<12> get_vendor_string();

struct VersionInfo {
    std::uint32_t stepping_id:4;
    std::uint32_t model:4;
    std::uint32_t family_id:4;
    std::uint32_t proc_type:2;
    std::uint32_t res:2;
    std::uint32_t ext_model_id:4;
    std::uint32_t ext_family_id:8;
    std::uint32_t res2:4;
};

VersionInfo get_version_info();

struct AuxInfo {
    std::uint32_t brand_index:8;
    std::uint32_t clflush_line_size:8;
    std::uint32_t max_num_cpus:8;
    std::uint32_t initial_apic_id:8;
};

AuxInfo get_aux_info();

struct FeatureInfo {
    std::uint32_t sse3:1; // SSE3 extensions
    std::uint32_t pclmulqdq:1; // Carryless Multiplication
    std::uint32_t dtes64:1; // 64-bit DS Area
    std::uint32_t monitor:1; // MONITOR/MWAIT
    std::uint32_t ds_cpl:1; // CPL Qualified Debug Store
    std::uint32_t vmx:1; // Virtual Machine Extensions
    std::uint32_t smx:1; // Safer Mode Extensions
    std::uint32_t est:1; // Enhanced Intel SpeedStep Technology
    std::uint32_t tm2:1; // Thermal Monitor 2
    std::uint32_t ssse3:1; // SSSE3 Extensions
    std::uint32_t cnxt_id:1; // L1 Context ID
    std::uint32_t res:1;
    std::uint32_t fma:1; // Fused Multiply Add
    std::uint32_t cmpxchg16b:1;
    std::uint32_t xtpr_update_control:1;
    std::uint32_t pdcm:1; // Perf/Debug Capability MSR
    std::uint32_t res2:1;
    std::uint32_t pcid:1; // Process-context Identifiers
    std::uint32_t dca:1; // Direct Cache Access
    std::uint32_t sse4_1:1; // SSE4.1
    std::uint32_t sse4_2:1; // SSE4.2
    std::uint32_t x2apic:1;
    std::uint32_t movbe:1;
    std::uint32_t popcnt:1;
    std::uint32_t tsc_deadline:1;
    std::uint32_t aes:1;
    std::uint32_t xsave:1;
    std::uint32_t osxsave:1;
    std::uint32_t avx:1;
    std::uint32_t f16c:1;
    std::uint32_t rdrand:1;
    std::uint32_t zero:1;

    std::uint32_t fpu:1; // x87 FPU on Chip
    std::uint32_t vme:1; // Virtual-8086 Mode Enhancement
    std::uint32_t de:1; // Debugging Extensions
    std::uint32_t pse:1; // Page Size Extensions
    std::uint32_t tsc:1; // Time Stamp Counter
    std::uint32_t msr:1; // RDMSR and WRMSR Support
    std::uint32_t pae:1; // Physical Address Extensions
    std::uint32_t mce:1; // Machine Check Exception
    std::uint32_t cx8:1; // CMPXCHG8B Inst.
    std::uint32_t apic:1; // APIC on Chip
    std::uint32_t res3:1;
    std::uint32_t sep:1; // SYSENTER and SYSEXIT
    std::uint32_t mtrr:1; // Memory Type Range Registers
    std::uint32_t pge:1; // PTE Global Bit
    std::uint32_t mca:1; // Machine Check Architecture
    std::uint32_t cmov:1; // Conditional Move/Compare Instruction
    std::uint32_t pat:1; // Page Attribute Table
    std::uint32_t pse_36:1; // Page Size Extension
    std::uint32_t psn:1; // Processor Serial Number
    std::uint32_t clfsh:1; // CFLUSH instruction
    std::uint32_t res4:1;
    std::uint32_t ds:1; // Debug Store
    std::uint32_t acpi:1; // Thermal Monitor and Clock Ctrl
    std::uint32_t mmx:1; // MMX Technology
    std::uint32_t fxsr:1; // FXSAVE/FXRSTOR
    std::uint32_t sse:1; // SSE Extensions
    std::uint32_t sse2:1; // SSE2 Extensions
    std::uint32_t ss:1; // Self Snoop
    std::uint32_t htt:1; // Multi-threading
    std::uint32_t tm:1; // Therm. Monitor
    std::uint32_t res5:1;
    std::uint32_t pbe:1; // Pend. Brk. EN.
};

FeatureInfo get_feature_info();

} // namespace Cpuid end
