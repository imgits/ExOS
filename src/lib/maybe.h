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

#include <type_traits>
#include "lib/assert.h"

// Generalized concept of optional values.
// It transparently handles lvalue-references, making raw pointers as a means
// of optional references obsolete.

class None { }; // Type of "No data"

namespace _Private {

// This stuff here is needed to transparently handle lvalue references.
// If T (the type being wrapped by Maybe<>) is a reference, we want to
// store a pointer (since we cannot store a reference).
// Thus we need to take the address of the argument of the constructor
// if, and _only_ if, the argument is a reference.
// Likewise, get() needs to dereference the data if it is a reference,
// but not if it's not a reference.
//
// Since we cannot partially specialize functions, we partially specialize
// a dummy struct which wraps the functions for us.
// As another limitation, we sadly need to do this outside of the Maybe class.

template <class T, class U, bool B = std::is_lvalue_reference<T>::value>
struct dummy { };

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

}

template <class T>
class Maybe {
private:
    static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
    using U = std::conditional_t<is_ref, std::add_pointer_t<T>, T>;

    // Wrap the dummy structs's functions for convenience.

    static constexpr U construct(T x)
    {
        return _Private::dummy<T, U>::construct(x);
    }

    static constexpr T ret(U x)
    {
        return _Private::dummy<T, U>::ret(x);
    }

    Either<U, None> m_data;

public:
    constexpr Maybe(T x)
    : m_data(construct(x))
    {
    }

    constexpr Maybe(None x)
    : m_data(x)
    {
    }

    constexpr T get() const
    {
        assert(is_some());
        return ret(m_data.left());
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
