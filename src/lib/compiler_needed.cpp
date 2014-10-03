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

#include <cstddef>

// Symbols needed by the compiler, even when freestanding.

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

extern "C" void *memset(void *b, int c, std::size_t len)
{
    auto a = reinterpret_cast<unsigned char *>(b);

    for (std::size_t i = 0; i < len; ++i)
    {
        a[i] = static_cast<unsigned char>(c);
    }

    return b;
}

extern "C" void __bzero(void *s, std::size_t n)
{
    memset(s, 0, n);
}

#pragma clang diagnostic pop
