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

#include <type_traits>
#include <cstddef>
#include <cstdint>

// Various utility functions.

template <class T>
constexpr auto to_underlying_type(T x)
{
    return static_cast<std::underlying_type_t<T>>(x);
}

template <class T>
constexpr void set_array(T *ptr, T c, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i)
        ptr[i] = c;
}

template <class T>
constexpr void reverse_array_inplace(T *ptr, std::size_t n)
{
    for (std::size_t i = n - 1, j = 0; j < i; --i, ++j) {
        T x = ptr[i];
        ptr[i] = ptr[j];
        ptr[j] = x;
    }
}

template <class T>
constexpr bool are_memory_equal(T const &x, T const &y)
{
    auto a = reinterpret_cast<std::uint8_t const *>(&x);
    auto b = reinterpret_cast<std::uint8_t const *>(&y);

    for (std::size_t i = 0; i < sizeof(T); ++i)
        if (a[i] != b[i])
            return false;

    return true;
}

template <class T>
constexpr auto unsigned_abs(T x)
{
    return static_cast<std::make_unsigned_t<T>>(x < 0 ? -x : x);
}
