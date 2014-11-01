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
#include "lib/ctstring.h"
#include "lib/math.h"

#include "framebuffer/framebuffer.h"

// printf() and snprintf()-like functions featuring format string checking
// at compile time. They return the number of characters written.
//
// Since the format string is validated at compile time, the runtime
// formatting function can avoid unneeded checks for validity.

namespace _Private {

enum class Case : uint8_t {
    LOWER,
    UPPER
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

struct ConvFlags {
    unsigned min_field_width;
    Case letter_case;
    uint8_t base;
    char pad_char;
};

#pragma clang diagnostic pop

size_t to_string(MutStringRef &buf, ConvFlags flags, StringRef arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, char arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, const void *arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, int arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, long long arg);
size_t to_string(MutStringRef &buf, ConvFlags flags, unsigned long long arg);

template <class T>
constexpr ConvFlags default_flags()
{
    return ConvFlags {
        .base = 10,
        .letter_case = Case::LOWER,
        .pad_char = ' ',
        .min_field_width = 0
    };
}

template <>
constexpr ConvFlags default_flags<const void *>()
{
    return ConvFlags {
        .base = 16,
        .letter_case = Case::LOWER,
        .pad_char = ' ',
        .min_field_width = 0
    };
}

template <>
constexpr ConvFlags default_flags<void *>()
{
    return default_flags<const void *>();
}

// These two format() functions handle formatting the arguments at runtime.
// They are able to ommit certain checks since they can rely on the validity
// of the format string (which is determined at compile-time).
size_t format(MutStringRef &buf, StringRef fmt);

template <class Arg, class... Args>
constexpr size_t format(MutStringRef &buf, StringRef fmt, Arg arg, Args... args)
{
    size_t i = 0, cnt = 0;

    for (;;) {
        if (fmt[i] != '(') {
            ++cnt;

            if (buf.is_space_left())
                buf.push_back(fmt[i]);

            ++i;

            continue;
        }

        ++i;

        if (fmt[i] == '(') {
            ++cnt;

            if (buf.is_space_left())
                buf.push_back('(');

            ++i;

            continue;
        }

        break;
    }

    ConvFlags flags = default_flags<Arg>();

    if (fmt[i] == '0') {
        flags.pad_char = '0';
        ++i;
    }

    StringRef end(nullptr, 0);
    Maybe<unsigned> min_length = fmt.slice_from(i).to_number<unsigned>(Radix(10), end);
    if (min_length.is_some()) {
        flags.min_field_width = min_length.get();
        i += fmt.slice_from(i).length() - end.length();
    }

    switch (fmt[i]) {
    case 'x':
        flags.base = 16;
        flags.letter_case = Case::LOWER;
        ++i;
        break;
    case 'X':
        flags.base = 16;
        flags.letter_case = Case::UPPER;
        ++i;
        break;
    case 'o':
        flags.base = 8;
        flags.letter_case = Case::LOWER;
        ++i;
        break;
    }

    ++i;

    size_t tmp = to_string(buf, flags, arg);

    assert(!add_overflow(cnt, tmp, cnt));

    tmp = format(buf, fmt.slice_from(i), args...);

    assert(!add_overflow(cnt, tmp, cnt));

    return cnt;
}

// Checking if the given flags are valid for a given argument type.

template <class T>
constexpr bool flags_valid(StringRef fmt);

template <>
constexpr bool flags_valid<long long>(StringRef fmt)
{
    if (fmt.length() == 0)
        return true;

    size_t i = 0;

    if (fmt[i] == '0') {
        ++i;

        if (i == fmt.length())
            return false;
    }

    while (fmt[i] >= '0' && fmt[i] <= '9') {
        ++i;

        if (i == fmt.length())
            return true;
    }

    if (i == fmt.length())
        return true;

    return false;
}

template <>
constexpr bool flags_valid<unsigned long long>(StringRef fmt)
{
    if (fmt.length() == 0)
        return true;

    size_t i = 0;

    if (fmt[i] == '0') {
        ++i;

        if (i == fmt.length())
            return false;
    }

    while (fmt[i] >= '0' && fmt[i] <= '9') {
        ++i;

        if (i == fmt.length())
            return true;
    }

    if (fmt[i] == 'x' || fmt[i] == 'X' || fmt[i] == 'o') {
        ++i;

        if (i == fmt.length())
            return true;
    }

    if (i == fmt.length())
        return true;

    return false;
}

template <>
constexpr bool flags_valid<StringRef>(StringRef fmt)
{
    return fmt.length() == 0;
}

template <>
constexpr bool flags_valid<char>(StringRef fmt)
{
    return fmt.length() == 0;
}

template <>
constexpr bool flags_valid<unsigned char>(StringRef fmt)
{
    return flags_valid<unsigned long long>(fmt);
}

template <>
constexpr bool flags_valid<const void *>(StringRef fmt)
{
    return flags_valid<unsigned long long>(fmt);
}

template <>
constexpr bool flags_valid<void *>(StringRef fmt)
{
    return flags_valid<const void *>(fmt);
}

template <>
constexpr bool flags_valid<int>(StringRef fmt)
{
    return flags_valid<long long>(fmt);
}

template <>
constexpr bool flags_valid<unsigned>(StringRef fmt)
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
    for (size_t i = 0; i < fmt.length(); ++i) {
        if (fmt[i] != '(')
            continue;

        if (i + 1 != fmt.length() && fmt[i + 1] == '(') {
            ++i;
            continue;
        }

        const size_t begin_flags = i + 1;

        const Maybe<size_t> index = fmt.slice_from(begin_flags).index_of(')');
        if (index.is_none())
            return false;

        const size_t end_flags = begin_flags + index.get();

        if (!flags_valid<Arg>(fmt.slice_from_until(begin_flags, end_flags)))
            return false;

        return is_valid<Args...>(fmt.slice_from(end_flags + 1));
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
        if (fmt[i] == '(' && (i + 1 == fmt.length() || fmt[i++ + 1] != '('))
            return false;

    return true;
}

} // end namespace _Private

// Type safe version of C's snprintf(), with compile-time checked format
// strings.
template <char... Fmt, class... Args>
constexpr size_t snprintf(MutStringRef &buf, CTString<Fmt...>, Args ...args)
{
    constexpr String<sizeof...(Fmt)> fmt = { { Fmt... } };

    static_assert(_Private::is_valid<Args...>(fmt.ref()), "Invalid format string!");

    return _Private::format(buf, fmt.ref(), args...);
}

// Type safe version of C's printf(), with compile-time checked format strings.
// Currently has a hard limit on the output size.
template <char... Fmt, class... Args>
constexpr size_t printf(CTString<Fmt...> fmt, Args ...args)
{
    String<2048> buf;
    MutStringRef mut_ref = buf.mut_ref();

    snprintf(mut_ref, fmt, args...);

    Framebuffer::put_string(mut_ref.to_immut_ref());

    return mut_ref.size();
}
