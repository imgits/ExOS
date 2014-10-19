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

#include "lib/printf.h"

#include "lib/util.h"
#include "lib/assert.h"

namespace {

char digit_to_ascii(unsigned char c, _Private::Case letter_case)
{
    static constexpr Array<char, 37> lowercase_letters = { "0123456789abcdefghijklmnopqrstuvwxyz" };
    static constexpr Array<char, 37> uppercase_letters = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

    assert(c <= 36);

    switch (letter_case) {
    case _Private::Case::LOWER: return lowercase_letters[c];
    case _Private::Case::UPPER: return uppercase_letters[c];
    }
}

} // anonymous namespace end

size_t _Private::to_string(MutStringRef &buf, ConvFlags, StringRef arg)
{
    for (const char c : arg)
        if (buf.is_space_left())
            buf.push_back(c);

    return arg.length();
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, int arg)
{
    return to_string(buf, flags, static_cast<long long>(arg));
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, unsigned arg)
{
    return to_string(buf, flags, static_cast<unsigned long long>(arg));
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, long arg)
{
    return to_string(buf, flags, static_cast<long long>(arg));
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, unsigned long arg)
{
    return to_string(buf, flags, static_cast<unsigned long long>(arg));
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, const void *arg)
{
    return to_string(buf, flags, reinterpret_cast<uintptr_t>(arg));
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, unsigned long long arg)
{
    assert(flags.base >= 2);
    assert(flags.base <= 36);

    size_t cnt = 0;

    const size_t start = buf.size();

    do {
        ++cnt;

        if (buf.is_space_left()) {
            auto x = static_cast<unsigned char>(arg % flags.base);
            buf.push_back(digit_to_ascii(x, flags.letter_case));
        }

        if (flags.min_field_width > 0)
            --flags.min_field_width;

        arg /= flags.base;
    } while (arg != 0);

    for (; flags.min_field_width-->0; ) {
        ++cnt;

        if (buf.is_space_left())
            buf.push_back(flags.pad_char);
    }

    buf.reverse_inplace(start, buf.size() - start);

    return cnt;
}

size_t _Private::to_string(MutStringRef &buf, ConvFlags flags, long long arg)
{
    size_t cnt = 0;

    if (arg < 0) {
        ++cnt;

        if (buf.is_space_left())
            buf.push_back('-');

        if (flags.min_field_width > 0)
            --flags.min_field_width;
    }

    return cnt + to_string(buf, flags, unsigned_abs(arg));
}

size_t _Private::format(MutStringRef &buf, StringRef fmt)
{
    size_t cnt = 0;

    for (size_t i = 0; i < fmt.length(); ++i) {
        if (fmt[i] == '(' && fmt[i + 1] == '(')
            ++i;

        ++cnt;

        if (buf.is_space_left())
            buf.push_back(fmt[i]);
    }

    return cnt;
}
