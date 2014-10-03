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
#include "lib/error.h"
#include "lib/assert.h"

// Represents either a value of type T or an error. Use this instead of
// seperate error codes and out-parameters.

template <class T>
class ValueOrError
{
private:
    Either<T, Error> m_data;

public:
    constexpr ValueOrError(T val)
    : m_data(val)
    {
    }

    constexpr ValueOrError(Error err)
    : m_data(err)
    {
    }

    constexpr T value() const
    {
        assert(is_value());
        return m_data.left();
    }

    constexpr Error error() const
    {
        assert(is_error());
        return m_data.right();
    }

    constexpr bool is_value() const
    {
        return m_data.is_left();
    }

    constexpr bool is_error() const
    {
        return m_data.is_right();
    }
};
