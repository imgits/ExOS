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

namespace {

void cpuid(uint32_t eax_in, uint32_t ecx_in, uint32_t &eax_out,
           uint32_t &ebx_out, uint32_t &ecx_out, uint32_t &edx_out)
{
    __asm__("cpuid"
            : "=a"(eax_out), "=b"(ebx_out), "=c"(ecx_out), "=d"(edx_out)
            : "a"(eax_in), "c"(ecx_in));
}

uint32_t g_largest_standard_function;

String<12> g_vendor_string;

Cpuid::IdentInfo g_ident_info;

Cpuid::MiscInfo g_misc_info;

Cpuid::FeatureInfo g_feature_info;

} // end anonymous namespace

void Cpuid::initialize()
{
    uint32_t eax, ebx, ecx, edx;

    cpuid(0, 0, eax, ebx, ecx, edx);

    g_largest_standard_function = eax;

    union {
        String<12> x;
        uint32_t regs[3];
    } u;

    cpuid(0, 0, eax, u.regs[0], u.regs[2], u.regs[1]);

    g_vendor_string = u.x;

    union {
        IdentInfo x;
        uint32_t eax;
    } u2;

    cpuid(1, 0, u2.eax, ebx, ecx, edx);

    g_ident_info = u2.x;

    union {
        MiscInfo x;
        uint32_t ebx;
    } u3;

    cpuid(1, 0, eax, u3.ebx, ecx, edx);

    g_misc_info = u3.x;

    union {
        FeatureInfo x;
        uint32_t ecx_edx[2];
    } u4;

    cpuid(0, 1, eax, ebx, u4.ecx_edx[0], u4.ecx_edx[1]);

    g_feature_info = u4.x;
}

uint32_t Cpuid::get_largest_standard_function()
{
    return g_largest_standard_function;
}

String<12> Cpuid::get_vendor_string()
{
    return g_vendor_string;
}

Cpuid::IdentInfo Cpuid::get_version_info()
{
    return g_ident_info;
}

Cpuid::MiscInfo Cpuid::get_misc_info()
{
    return g_misc_info;
}

Cpuid::FeatureInfo Cpuid::get_feature_info()
{
    return g_feature_info;
}
