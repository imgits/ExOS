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

#pragma once

#include <cstddef>

#include "lib/assert.h"
#include "lib/maybe.h"

// Reference to an immutable(const) array. Small enough to be passed by-value.

template <class T>
class ImmutArrayRef {
private:
    const T *m_ptr;
    size_t m_size;

public:
    explicit constexpr ImmutArrayRef(const T *s, size_t l)
    : m_ptr(s)
    , m_size(l)
    {
    }

    constexpr const T *data() const
    {
        return m_ptr;
    }

    constexpr size_t length() const
    {
        return m_size;
    }

    constexpr const T &operator[](size_t i) const
    {
        assert(i < m_size);
        return m_ptr[i];
    }

    constexpr ImmutArrayRef<T> slice_from(size_t begin) const
    {
        assert(begin <= m_size);
        return ImmutArrayRef<T>(m_ptr + begin, m_size - begin);
    }

    constexpr ImmutArrayRef<T> slice_from_until(size_t begin, size_t end) const
    {
        assert(begin < m_size);
        assert(end < m_size);
        assert(end >= begin);
        return ImmutArrayRef<T>(m_ptr + begin, end - begin);
    }

    constexpr Maybe<size_t> index_of(const T &x) const
    {
        for (size_t i = 0; i < m_size; ++i)
            if (m_ptr[i] == x)
                return i;

        return Unit::NONE;
    }
};

template <class T>
constexpr const T *begin(ImmutArrayRef<T> x)
{
    return x.data();
}

template <class T>
constexpr const T *end(ImmutArrayRef<T> x)
{
    return x.data() + x.length();
}

using StringRef = ImmutArrayRef<char>;

constexpr StringRef operator"" _s(const char *s, size_t l)
{
    return StringRef(s, l);
}
