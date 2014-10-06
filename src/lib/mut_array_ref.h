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

#include "lib/immut_array_ref.h"
#include "lib/util.h"
#include "lib/assert.h"

// Reference to a mutable array. Usually you want to mutate the array this
// refers to, so pass it as a non-const reference. If you feel the need to pass
// it as a const reference, consider using the method "to_immut_ref()".

template <class T>
class MutArrayRef {
private:
    T *m_ptr;
    size_t m_capacity;
    size_t m_curr_idx;

public:
    template <size_t N>
    explicit constexpr MutArrayRef(T(&ptr)[N])
    : m_ptr(ptr)
    , m_capacity(N)
    , m_curr_idx(0)
    {
    }

    constexpr void push_back(T const &x)
    {
        assert(m_curr_idx < m_capacity);
        m_ptr[m_curr_idx++] = x;
    }

    constexpr bool is_space_left() const
    {
        return m_curr_idx < m_capacity;
    }

    constexpr ImmutArrayRef<T> to_immut_ref() const
    {
        return ImmutArrayRef<T>(m_ptr, m_curr_idx);
    }

    constexpr size_t capacity() const
    {
        return m_capacity;
    }

    constexpr size_t curr_idx() const
    {
        return m_curr_idx;
    }

    constexpr void reverse_inplace(size_t start, size_t n)
    {
        assert(start <= m_curr_idx);
        assert(n <= m_curr_idx);
        reverse_array_inplace(m_ptr + start, n);
    }
};

using MutStringRef = MutArrayRef<char>;
using MutStringRefUefi = MutArrayRef<char16_t>;
