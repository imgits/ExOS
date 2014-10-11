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

#include "asm/asm.h"

void Asm::clgi()
{
    __asm__("clgi");
}

void Asm::cli()
{
    __asm__("cli");
}

void Asm::clts()
{
    __asm__("clts");
}

void Asm::hlt()
{
    __asm__("hlt");
    __builtin_unreachable();
}

void Asm::invd()
{
    __asm__("invd");
}

void Asm::invlpg(uint64_t page)
{
    __asm__("invlpg [page]" : : [page]"m"(page));
}

void Asm::wbinvd()
{
    __asm__("wbinvd");
}

void Asm::lgdt(const Descriptors::TableRegister &dtr)
{
    __asm__("lgdt %[dtr]" : : [dtr]"m"(dtr));
}

void Asm::lidt(const Descriptors::TableRegister &dtr)
{
    __asm__("lidt %[dtr]" : : [dtr]"m"(dtr));
}

void Asm::sgdt(Descriptors::TableRegister &dtr)
{
    __asm__("sgdt %[dtr]" : : [dtr]"m"(dtr));
}

void Asm::sidt(Descriptors::TableRegister &dtr)
{
    __asm__("sidt %[dtr]" : : [dtr]"m"(dtr));
}

void Asm::reload_cs_register(Descriptors::SegmentSelector selector)
{
    uint64_t dummy;
    __asm__("pushq %[selector];"
            "leaq label(%%rip), %[dummy];"
            "pushq %[dummy];"
            "lretq;"
            "label:"
            : [dummy]"=r"(dummy)
            : [selector]"m"(selector)
            : "memory");
}

uint64_t Asm::rdmsr(uint32_t msr)
{
    union {
        uint64_t x;
        uint32_t regs[2];
    } u;

    __asm__("rdmsr"
            : "=c"(msr)
            : "a"(u.regs[0]), "d"(u.regs[1]));

    return u.x;
}

void Asm::wrmsr(uint32_t msr, uint64_t value)
{
    union {
        uint64_t x;
        uint32_t regs[2];
    } u = {
        .x = value
    };

    __asm__("wrmsr" : : "c"(msr), "a"(u.regs[0]), "d"(u.regs[1]));
}
