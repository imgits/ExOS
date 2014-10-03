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

#include <cstdint>

#include "lib/assert.h"

// Tagged union for 2 data members.

enum class Tag : std::uint8_t
{
    LEFT,
    RIGHT
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

template <class T, class U>
class Either
{
private:
    union
    {
        T m_left;
        U m_right;
    };
    Tag m_tag;

public:
    constexpr Either(T x)
    : m_left(x)
    , m_tag(Tag::LEFT)
    {
    }

    constexpr Either(U x)
    : m_right(x)
    , m_tag(Tag::RIGHT)
    {
    }

    constexpr T left() const
    {
        assert(is_left());
        return m_left;
    }

    constexpr U right() const
    {
        assert(is_right());
        return m_right;
    }

    constexpr bool is_left() const
    {
        return m_tag == Tag::LEFT;
    }

    constexpr bool is_right() const
    {
        return m_tag == Tag::RIGHT;
    }
};

#pragma clang diagnostic pop
