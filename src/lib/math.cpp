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

#include "lib/math.h"

bool add_overflow(unsigned x, unsigned y, unsigned &sum)
{
    return __builtin_uadd_overflow(x, y, &sum);
}

bool add_overflow(unsigned long x, unsigned long y, unsigned long &sum)
{
    return __builtin_uaddl_overflow(x, y, &sum);
}

bool add_overflow(unsigned long long x, unsigned long long y, unsigned long long &sum)
{
    return __builtin_uaddll_overflow(x, y, &sum);
}

bool add_overflow(int x, int y, int &sum)
{
    return __builtin_sadd_overflow(x, y, &sum);
}

bool add_overflow(long x, long y, long &sum)
{
    return __builtin_saddl_overflow(x, y, &sum);
}

bool add_overflow(long long x, long long y, long long &sum)
{
    return __builtin_saddll_overflow(x, y, &sum);
}

bool sub_overflow(unsigned x, unsigned y, unsigned &diff)
{
    return __builtin_usub_overflow(x, y, &diff);
}

bool sub_overflow(unsigned long x, unsigned long y, unsigned long &diff)
{
    return __builtin_usubl_overflow(x, y, &diff);
}

bool sub_overflow(unsigned long long x, unsigned long long y, unsigned long long &diff)
{
    return __builtin_usubll_overflow(x, y, &diff);
}

bool sub_overflow(int x, int y, int &diff)
{
    return __builtin_ssub_overflow(x, y, &diff);
}

bool sub_overflow(long x, long y, long &diff)
{
    return __builtin_ssubl_overflow(x, y, &diff);
}

bool sub_overflow(long long x, long long y, long long &diff)
{
    return __builtin_ssubll_overflow(x, y, &diff);
}

bool mul_overflow(unsigned x, unsigned y, unsigned &prod)
{
    return __builtin_umul_overflow(x, y, &prod);
}

bool mul_overflow(unsigned long x, unsigned long y, unsigned long &prod)
{
    return __builtin_umull_overflow(x, y, &prod);
}

bool mul_overflow(unsigned long long x, unsigned long long y, unsigned long long &prod)
{
    return __builtin_umulll_overflow(x, y, &prod);
}

bool mul_overflow(int x, int y, int &prod)
{
    return __builtin_smul_overflow(x, y, &prod);
}

bool mul_overflow(long x, long y, long &prod)
{
    return __builtin_smull_overflow(x, y, &prod);
}

bool mul_overflow(long long x, long long y, long long &prod)
{
    return __builtin_smulll_overflow(x, y, &prod);
}
