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

#include "cpuid/cpuid.h"

void Cpuid::cpuid(uint32_t eax_in, uint32_t ecx_in, uint32_t &eax_out,
                  uint32_t &ebx_out, uint32_t &ecx_out, uint32_t &edx_out)
{
    __asm__("cpuid"
            : "=a"(eax_out), "=b"(ebx_out), "=c"(ecx_out), "=d"(edx_out)
            : "a"(eax_in), "c"(ecx_in));
}

uint32_t Cpuid::get_largest_standard_function()
{
    uint32_t eax, ebx, ecx, edx;

    cpuid(0, 0, eax, ebx, ecx, edx);

    return eax;
}

String<12> Cpuid::get_vendor_string()
{
    union {
        String<12> x;
        uint32_t regs[3];
    } u;
    uint32_t eax;

    cpuid(0, 0, eax, u.regs[0], u.regs[2], u.regs[1]);

    return u.x;
}

Cpuid::IdentInfo Cpuid::get_version_info()
{
    union {
        IdentInfo x;
        uint32_t eax;
    } u;
    uint32_t ebx, ecx, edx;

    cpuid(1, 0, u.eax, ebx, ecx, edx);

    return u.x;
}

Cpuid::MiscInfo Cpuid::get_misc_info()
{
    union {
        MiscInfo x;
        uint32_t ebx;
    } u;
    uint32_t eax, ecx, edx;

    cpuid(1, 0, eax, u.ebx, ecx, edx);

    return u.x;
}

Cpuid::FeatureInfo Cpuid::get_feature_info()
{
    union {
        FeatureInfo x;
        uint32_t ecx_edx[2];
    } u;
    uint32_t eax, ebx;

    cpuid(0, 1, eax, ebx, u.ecx_edx[0], u.ecx_edx[1]);

    return u.x;
}
