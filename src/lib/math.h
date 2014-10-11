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

bool add_overflow(unsigned x, unsigned y, unsigned &sum);
bool add_overflow(unsigned long x, unsigned long y, unsigned long &sum);
bool add_overflow(unsigned long long x, unsigned long long y, unsigned long long &sum);
bool add_overflow(int x, int y, int &sum);
bool add_overflow(long x, long y, long &sum);
bool add_overflow(long long x, long long y, long long &sum);

bool sub_overflow(unsigned x, unsigned y, unsigned &diff);
bool sub_overflow(unsigned long x, unsigned long y, unsigned long &diff);
bool sub_overflow(unsigned long long x, unsigned long long y, unsigned long long &diff);
bool sub_overflow(int x, int y, int &diff);
bool sub_overflow(long x, long y, long &diff);
bool sub_overflow(long long x, long long y, long long &diff);

bool mul_overflow(unsigned x, unsigned y, unsigned &prod);
bool mul_overflow(unsigned long x, unsigned long y, unsigned long &prod);
bool mul_overflow(unsigned long long x, unsigned long long y, unsigned long long &prod);
bool mul_overflow(int x, int y, int &prod);
bool mul_overflow(long x, long y, long &prod);
bool mul_overflow(long long x, long long y, long long &prod);
