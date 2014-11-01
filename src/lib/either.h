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
#include <type_traits>

#include "lib/assert.h"

// Tagged union for 2 data members.

enum class Tag : uint8_t {
    LEFT,
    RIGHT
};

namespace _Private {

// This stuff here is needed to transparently handle lvalue references.
// If the types being wrapped by Either are references, we want to
// store pointers (since we cannot store references).
// Thus we need to take the address of the argument of the constructor
// if, and _only_ if, the argument is a reference.
// Likewise, left()/right() need to dereference the data if it is a reference,
// but not if it's not a reference.
//
// Since we cannot partially specialize functions, we partially specialize
// a dummy struct which wraps the functions for us.
// As another limitation, we sadly need to do this outside the class.

template <class T, class U, bool B = std::is_lvalue_reference<T>::value>
struct dummy;

template <class T, class U>
struct dummy<T, U, true> {
    // T is a reference type.

    static constexpr U construct(T x)
    {
        return &x;
    }

    static constexpr T ret(U x)
    {
        return *x;
    }
};

template <class T, class U>
struct dummy<T, U, false> {
    // T is not a reference type.

    static constexpr U construct(T x)
    {
        return x;
    }

    static constexpr T ret(U x)
    {
        return x;
    }
};

} // end namespace _Private

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

template <class T, class U>
class Either {
private:
    static constexpr bool left_is_ref = std::is_lvalue_reference<T>::value;
    using A = std::conditional_t<left_is_ref, std::add_pointer_t<T>, T>;

    static constexpr bool right_is_ref = std::is_lvalue_reference<U>::value;
    using B = std::conditional_t<right_is_ref, std::add_pointer_t<U>, U>;

    // Wrap the dummy structs's functions for convenience.

    static constexpr A construct(T x)
    {
        return _Private::dummy<T, A>::construct(x);
    }

    static constexpr B construct(U x)
    {
        return _Private::dummy<U, B>::construct(x);
    }

    static constexpr T ret(A x)
    {
        return _Private::dummy<T, A>::ret(x);
    }

    static constexpr U ret(B x)
    {
        return _Private::dummy<U, B>::ret(x);
    }

    union {
        A m_left;
        B m_right;
    };
    Tag m_tag;

public:
    constexpr Either(T x)
    : m_left(construct(x))
    , m_tag(Tag::LEFT)
    {
    }

    constexpr Either(U x)
    : m_right(construct(x))
    , m_tag(Tag::RIGHT)
    {
    }

    constexpr T left() const
    {
        assert(is_left());
        return ret(m_left);
    }

    constexpr U right() const
    {
        assert(is_right());
        return ret(m_right);
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
