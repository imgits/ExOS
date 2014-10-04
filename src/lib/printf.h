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

template <size_t N>
constexpr size_t to_string(MutStringRef &buf, ConvFlags, String<N> const &str)
{
    for (char const c : str)
    {
        if (buf.is_space_left())
        {
            buf.push_back(c);
        }
    }

    return N;
}

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
            switch (fmt[i])
            {
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
            case 'O':
                flags.base = 8;
                flags.letter_case = Case::UPPER;
                break;
            }
        }

        ++i;

        cnt += to_string(buf, flags, arg);

        return cnt + format(buf, fmt.slice_from(i), args...);
    }

    return cnt;
}

constexpr bool is_valid(StringRef fmt)
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

constexpr bool flags_valid(StringRef fmt, StringRef const &)
{
    return fmt.length() == 0;
}

template <size_t N>
constexpr bool flags_valid(StringRef fmt, String<N> const &)
{
    return fmt.length() == 0;
}

constexpr bool flags_valid(StringRef fmt, void const *const &)
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

constexpr bool flags_valid(StringRef fmt, void *const &)
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

constexpr bool flags_valid(StringRef fmt, int const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

constexpr bool flags_valid(StringRef fmt, unsigned int const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

constexpr bool flags_valid(StringRef fmt, long const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

constexpr bool flags_valid(StringRef fmt, unsigned long const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

constexpr bool flags_valid(StringRef fmt, long long const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

constexpr bool flags_valid(StringRef fmt, unsigned long long const &)
{
    for (char const c : fmt)
    {
        if (c != 'x' && c != 'X' && c != 'o' && c != 'O')
        {
            return false;
        }
    }
    return true;
}

template <class Arg, class... Args>
constexpr bool is_valid(StringRef fmt, Arg const &arg, Args const &... args)
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

        size_t begin_flags = i;

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

        size_t end_flags = i;

        if (!flags_valid(fmt.slice_from_until(begin_flags, end_flags), arg))
        {
            return false;
        }

        ++i;

        return is_valid(fmt.slice_from(i), args...);
    }

    return false;
}

template <char... Fmt, class... Args>
constexpr size_t snprintf(MutStringRef &buf, CTString<Fmt...>, Args... args)
{
    constexpr String<sizeof...(Fmt)> fmt = { { Fmt... } };

    static_assert(is_valid(fmt.ref(), args...), "Invalid format string!");

    return format(buf, fmt.ref(), args...);
}

extern Error (*print_func)(StringRef);

template <char... Fmt, class... Args>
constexpr ValueOrError<size_t> printf(CTString<Fmt...> fmt, Args... args)
{
    String<2048> buf;
    MutStringRef mut_ref = buf.mut_ref();

    size_t result = snprintf(mut_ref, fmt, args...);

    Error err = print_func(mut_ref.to_immut_ref());
    if (err != Error::SUCCESS)
    {
        return err;
    }

    return result;
}
