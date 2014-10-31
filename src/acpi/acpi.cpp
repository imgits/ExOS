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

#include "acpi/acpi.h"

void *Acpi::Xsdt::get_table(StringRef signature) const
{
    uint32_t len = header.length - sizeof(header);

    for (uint32_t i = 0; i < len; ++i) {
        TableHeader *head = reinterpret_cast<TableHeader *>(entries[i]);
        if (head->signature.ref() == signature)
            return head;
    }

    return nullptr;
}

template <>
Maybe<Acpi::Fadt &> Acpi::Xsdt::get_table<Acpi::Fadt>() const
{
    void *ret = get_table("FACP"_s);
    if (ret == nullptr)
        return None();

    return *static_cast<Fadt *>(ret);
}
