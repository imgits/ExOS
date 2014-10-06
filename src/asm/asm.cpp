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

void Asm::invlpg(uint8_t tlb_entry)
{
    __asm__("invlpg %[tlb_entry]" : : [tlb_entry] "mem"(tlb_entry));
}

void Asm::invlpga(uint64_t virtual_page, uint32_t asid)
{
    __asm__("invlpga %[virtual_page], %[asid]"
            :
            : [virtual_page] "a"(virtual_page), [asid] "c"(asid));
}

void Asm::lgdt(DescriptorTableRegister const &dtr)
{
    __asm__("lgdt %[dtr]" : : [dtr] "m"(dtr));
}

void Asm::lidt(DescriptorTableRegister const &dtr)
{
    __asm__("lidt %[dtr]" : : [dtr] "m"(dtr));
}

void Asm::reload_cs_register(SegmentSelector selector)
{
    uint64_t dummy;
    __asm__("pushq %[selector];"
            "leaq label(%%rip), %[dummy];"
            "pushq %[dummy];"
            "lretq;"
            "label:"
            : [dummy] "=r"(dummy)
            : [selector] "m"(selector)
            : "memory");
}
