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
#include <cstdint>

#include "lib/immut_array_ref.h"
#include "lib/mut_array_ref.h"
#include "lib/array.h"
#include "lib/value_or_error.h"
#include "lib/ctstring.h"

// printf() and snprintf()-like functions featuring format string checking
// at compile time. They either return the number of characters written or
// an error.
//
// Since the format string is validated at compile time, the runtime
// formatting function can avoid unneeded checks for validity.

enum class Case : uint8_t
{
    LOWER,
    UPPER
};

struct ConvFlags
{
    Case letter_case;
    uint8_t base;
};

size_t to_string(MutStringRef &buf, ConvFlags flags, StringRef arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, void const *arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, int arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned int arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, long long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned long long arg);

// These two format() functions handle formatting the arguments at runtime.
// They are able to ommit certain checks since they can rely on the validity
// of the format string (which is determined at compile-time).
size_t format(MutStringRef &buf, StringRef fmt);

template <class Arg, class... Args>
constexpr size_t format(MutStringRef &buf, StringRef fmt, Arg arg, Args... args)
{
    size_t cnt = 0;

    for (size_t i = 0;; ++i)
    {
        if (fmt[i] != '(')
        {
            ++cnt;

            if (buf.is_space_left())
            {
                buf.push_back(fmt[i]);
            }

            continue;
        }

        if (fmt[i + 1] == '(')
        {
            ++cnt;
            ++i;

            if (buf.is_space_left())
            {
                buf.push_back('(');
            }

            continue;
        }

        ++i;

        ConvFlags flags = { .base = 10, .letter_case = Case::LOWER };

        for (; fmt[i] != ')'; ++i)
        {
            switch (fmt[i]) {
            case 'x':
                flags.base = 16;
                flags.letter_case = Case::LOWER;
                break;
            case 'X':
                flags.base = 16;
                flags.letter_case = Case::UPPER;
                break;
            case 'o':
                flags.base = 8;
                flags.letter_case = Case::LOWER;
                break;
            }
        }

        ++i;

        cnt += to_string(buf, flags, arg);

        return cnt + format(buf, fmt.slice_from(i), args...);
    }

    return cnt;
}

// Checking if the given flags are valid for a given argument type.

template <class T>
constexpr bool flags_valid(StringRef fmt);

template <>
constexpr bool flags_valid<long long>(StringRef fmt)
{
    return fmt.length() == 0;
}

template <>
constexpr bool flags_valid<unsigned long long>(StringRef fmt)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o')
        {
            return false;
        }
    }
    return true;
}

template <>
constexpr bool flags_valid<StringRef>(StringRef fmt)
{
    return fmt.length() == 0;
}

template <>
constexpr bool flags_valid<void const *>(StringRef fmt)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X')
        {
            return false;
        }
    }
    return true;
}

template <>
constexpr bool flags_valid<void *>(StringRef fmt)
{
    return flags_valid<void const *>(fmt);
}

template <>
constexpr bool flags_valid<int>(StringRef fmt)
{
    return flags_valid<long long>(fmt);
}

template <>
constexpr bool flags_valid<unsigned int>(StringRef fmt)
{
    return flags_valid<unsigned long long>(fmt);
}

template <>
constexpr bool flags_valid<long>(StringRef fmt)
{
    return flags_valid<long long>(fmt);
}

template <>
constexpr bool flags_valid<unsigned long>(StringRef fmt)
{
    return flags_valid<unsigned long long>(fmt);
}

// The following is_valid() and is_valid_helper() functions determine the
// validity of the format string. They return true if they are valid and
// false if not.
// They are forced to be executed at compile-time by the static_assert()
// in snprintf().

template <class ...Ts>
constexpr bool is_valid(StringRef fmt);

// We need a helper function so that there's no ambiguity when is_valid()
// is called with an empty paramter pack.
template <class Arg, class... Args>
constexpr bool is_valid_helper(StringRef fmt)
{
    for (size_t i = 0; i < fmt.length(); ++i)
    {
        if (fmt[i] != '(')
        {
            continue;
        }

        if (i + 1 != fmt.length() && fmt[i + 1] == '(')
        {
            ++i;
            continue;
        }

        ++i;

        size_t const begin_flags = i;

        bool found = false;
        for (; i < fmt.length(); ++i)
        {
            if (fmt[i] == ')')
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return false;
        }

        size_t const end_flags = i;

        if (!flags_valid<Arg>(fmt.slice_from_until(begin_flags, end_flags)))
        {
            return false;
        }

        ++i;

        return is_valid<Args...>(fmt.slice_from(i));
    }

    return false;
}

template <class ...Ts>
constexpr bool is_valid(StringRef fmt)
{
    return is_valid_helper<Ts...>(fmt);
}

template <>
constexpr bool is_valid<>(StringRef fmt)
{
    for (size_t i = 0; i < fmt.length(); ++i)
    {
        if (fmt[i] == '(' && (i + 1 == fmt.length() || fmt[i++ + 1] != '('))
        {
            return false;
        }
    }

    return true;
}

// Type safe version of C's snprintf(), with compile-time checked format
// strings.
template <char... Fmt, class... Args>
constexpr size_t snprintf(MutStringRef &buf, CTString<Fmt...>, Args ...args)
{
    constexpr String<sizeof...(Fmt)> fmt = { { Fmt... } };

    static_assert(is_valid<Args...>(fmt.ref()), "Invalid format string!");

    return format(buf, fmt.ref(), args...);
}

// Pointer to the function that should be used by printf().
extern ValueOrError<size_t> (*printf_func)(StringRef);

// Type safe version of C's printf(), with compile-time checked format strings.
// Currently has a hard limit on the output size.
template <char... Fmt, class... Args>
constexpr ValueOrError<size_t> printf(CTString<Fmt...> fmt, Args ...args)
{
    String<2048> buf;
    MutStringRef mut_ref = buf.mut_ref();

    snprintf(mut_ref, fmt, args...);

    return printf_func(mut_ref.to_immut_ref());
}
