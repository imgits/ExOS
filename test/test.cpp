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

#include <iostream>

#include "lib/immut_array_ref.h"
#include "lib/array.h"
#include "lib/printf.h"

#include <cassert>

void test_strings()
{
    assert("1234"_s == "1234"_s);
    assert("abcd"_s != "ABCD"_s);
    assert("abcde"_s != "abcd"_s);

    StringRef end(nullptr, 0);
    Maybe<int> num = "-1234"_s.to_number<int>(None(), end);
    assert(num.is_some());
    assert(end.length() == 0);
    assert(num.get() == -1234);

    num = "12avshd"_s.to_number<int>(None(), end);
    assert(num.is_some());
    assert(num.get() == 12);
    assert(end == "avshd"_s);

    num = "qweer"_s.to_number<int>(None(), None());
    assert(num.is_none());

    Maybe<unsigned> num2 = "0xdeadbeef"_s.to_number<unsigned>(None(), None());
    assert(num2.is_some());
    assert(num2.get() == 0xdeadbeef);

    num2 = "deadbeef"_s.to_number<unsigned>(16, None());
    assert(num2.is_some());
    assert(num2.get() == 0xdeadbeef);

    assert("1234"_s.slice_from(2) == "34"_s);
    assert("1234"_s.slice_from_until(2, 3) == "3"_s);
    assert("1234"_s.slice_from(0) == "1234"_s);
    assert("1234"_s.slice_from_until(0, 4).slice_from(2) == "34"_s);
    assert("1234"_s.slice_from_until(0, 4) == "1234"_s);
}

void test_printf()
{
    String<1234> buf;
    MutStringRef mut_ref = buf.mut_ref();

    snprintf(mut_ref, "0x(08x) hallo (4) ()"_cts, 0xdeadU, 23, -4545);
    assert(mut_ref.to_immut_ref() == "0x0000dead hallo   23 -4545"_s);

    String<2> buf2;
    mut_ref = buf2.mut_ref();
    StringRef s = "test"_s;

    size_t ret = snprintf(mut_ref, "()"_cts, s);
    assert(mut_ref.to_immut_ref() == "te"_s);
    assert(ret == s.length());
}

int main()
{
    test_strings();
    test_printf();

    std::cout << "All tests passed!\n";

    return 0;
}
