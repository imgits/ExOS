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

#include "segmentation/gdt.h"

#include "asm/asm.h"

namespace {

union GdtEntry {
    Descriptors::CodeSegment cs;
    Descriptors::DataSegment ds;
    Descriptors::SystemSegment ss;
};

GdtEntry gdt[4];

} // end anonymous namespace

void Gdt::setup()
{
    gdt[0] = { };

    gdt[1].cs = {
        .conforming = 1,
        .one = 1,
        .one2 = 1,
        .descriptor_privilege_level = to_underlying_type(Descriptors::PrivilegeLevel::KERNEL),
        .present = 1,
        .long_attribute = 1,
        .default_operand_size = 0
    };

    gdt[2].cs = {
        .conforming = 1,
        .one = 1,
        .one2 = 1,
        .descriptor_privilege_level = to_underlying_type(Descriptors::PrivilegeLevel::USER),
        .present = 1,
        .long_attribute = 1,
        .default_operand_size = 0
    };

    const Descriptors::TableRegister gdtr = {
        .base_address = reinterpret_cast<uint64_t>(&gdt),
        .limit = sizeof(gdt) - 1
    };

    Asm::lgdt(gdtr);

    Asm::reload_cs_register(CS_SELECTOR_KERNEL);
}
