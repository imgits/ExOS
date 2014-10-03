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

#include "lib/either.h"

#include "lib/assert.h"

// Generalized concept of optional values.

enum class Unit : std::uint8_t
{
    NONE
};

template <class T>
class Maybe
{
private:
    Either<T, Unit> m_data;

public:
    constexpr Maybe(T x)
    : m_data(x)
    {
    }

    constexpr Maybe(Unit x)
    : m_data(x)
    {
    }

    constexpr T get() const
    {
        assert(is_some());
        return m_data.left();
    }

    constexpr bool is_some() const
    {
        return m_data.is_left();
    }

    constexpr bool is_none() const
    {
        return m_data.is_right();
    }
};
