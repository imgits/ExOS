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

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags, StringRef arg)
{
    for (const char c : arg)
        if (buf.is_space_left())
            buf.push_back(c);

    return arg.length();
}

static char digit_to_ascii(unsigned char c, Case letter_case)
{
    static constexpr char lowercase_letters[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    static constexpr char uppercase_letters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    switch (letter_case) {
    case Case::LOWER: return lowercase_letters[c];
    case Case::UPPER: return uppercase_letters[c];
    }
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, int arg)
{
    return to_string(buf, flags, static_cast<long long>(arg));
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, unsigned int arg)
{
    return to_string(buf, flags, static_cast<unsigned long long>(arg));
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, long arg)
{
    return to_string(buf, flags, static_cast<long long>(arg));
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, unsigned long arg)
{
    return to_string(buf, flags, static_cast<unsigned long long>(arg));
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags, const void *arg)
{
    ConvFlags flags = { .base = 16, .letter_case = Case::LOWER };
    return to_string(buf, flags, reinterpret_cast<uintptr_t>(arg));
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, unsigned long long arg)
{
    std::size_t cnt = 0;

    const std::size_t start = buf.curr_idx();

    do {
        ++cnt;

        if (buf.is_space_left()) {
            const unsigned char x = static_cast<unsigned char>(arg % flags.base);
            buf.push_back(digit_to_ascii(x, flags.letter_case));
        }

        arg /= flags.base;
    } while (arg != 0);

    buf.reverse_inplace(start, buf.curr_idx() - start);
    
    return cnt;
}

ValueOrError<std::size_t> to_string(MutStringRef &buf, ConvFlags flags, long long arg)
{
    std::size_t cnt = 0;

    if (arg < 0) {
        ++cnt;

        if (buf.is_space_left())
            buf.push_back('-');
    }

    ValueOrError<std::size_t> result = to_string(buf, flags, unsigned_abs(arg));
    if (result.is_error())
        return result.error();

    return cnt + result.value();
}

ValueOrError<std::size_t> format(MutStringRef &buf, StringRef fmt)
{
    std::size_t cnt = 0;

    for (std::size_t i = 0; i < fmt.length(); ++i) {
        if (fmt[i] == '(' && fmt[i + 1] == '(')
            ++i;

        ++cnt;

        if (buf.is_space_left())
            buf.push_back(fmt[i]);
    }
    
    return cnt;
}
