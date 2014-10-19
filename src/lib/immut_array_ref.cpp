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

#include "lib/immut_array_ref.h"

#include "lib/assert.h"
#include "lib/math.h"

// A char array can be parsed to a number.
template <>
template <class T>
Maybe<T> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const
{
    if (base.is_some()) {
        assert(base.get() >= 2);
        assert(base.get() <= 36);
    }

    if (m_size == 0)
        return None();

    size_t i = 0;

    while (m_ptr[i] == ' ') {
        ++i;

        if (i == m_size)
            return None();
    }

    bool negative = false;

    switch (m_ptr[i]) {
    case '+':
        ++i;

        if (i == m_size)
            return None();

        break;
    case '-':
        negative = true;

        ++i;

        if (i == m_size)
            return None();

        break;
    }

    unsigned radix;

    switch (m_ptr[i]) {
    case '0':
        ++i;

        if (i == m_size)
            return None();

        switch (m_ptr[i]) {
        case 'x':
        case 'X':
            ++i;

            if (i == m_size)
               return None();

            radix = 16;
            break;
        default:
            radix = 8;
            break;
        }
        break;
    default:
        radix = base.is_some() ? base.get() : 10;
        break;
    }

    size_t begin_num = i;

    T result = 0;

    for (;;) {
        char digit;
        if (m_ptr[i] >= '0' && m_ptr[i] <= '9')
            digit = m_ptr[i] - '0';
        else if (m_ptr[i] >= 'a' && m_ptr[i] <= 'z')
            digit = m_ptr[i] - 'a' + 0xa;
        else if (m_ptr[i] >= 'A' && m_ptr[i] <= 'Z')
            digit = m_ptr[i] - 'A' + 0xA;
        else
            break;

        if (static_cast<unsigned>(digit) >= radix)
            break;

        assert(!mul_overflow(result, static_cast<T>(radix), result));
        assert(!add_overflow(result, static_cast<T>(digit), result));

        ++i;

        if (i == m_size)
            break;
    }

    if (i == begin_num) // Whole string is garbage
        return None();

    if (negative)
        result = -result;

    if (i != m_size && end.is_some())
        end.get() = slice_from(i);

    return result;
}

// Explicit instantiation for all relevant types.
template Maybe<int> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;
template Maybe<unsigned> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;
template Maybe<long> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;
template Maybe<unsigned long> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;
template Maybe<long long> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;
template Maybe<unsigned long long> StringRef::to_number(Maybe<unsigned> base, Maybe<StringRef &> end) const;

bool operator==(StringRef x, StringRef y)
{
    if (x.length() != y.length())
        return false;

    for (size_t i = 0; i < x.length(); ++i)
        if (x[i] != y[i])
            return false;

    return true;
}

bool operator!=(StringRef x, StringRef y)
{
    return !(x == y);
}
