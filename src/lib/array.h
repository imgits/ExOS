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

#include "lib/mut_array_ref.h"
#include "lib/immut_array_ref.h"
#include "lib/assert.h"

// Replacement for C-style arrays.

template <class T, std::size_t N>
struct Array {
    T m_data[N];

    constexpr ImmutArrayRef<T> ref() const
    {
        return ImmutArrayRef<T>(m_data, N);
    }

    constexpr MutArrayRef<T> mut_ref()
    {
        return MutArrayRef<T>(m_data);
    }

    constexpr const T &operator[](std::size_t i) const
    {
        assert(i < N);
        return m_data[i];
    }
};

template <std::size_t N>
using String = Array<char, N>;
