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

#include "uefi/types.h"

constexpr EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID = {
    0x09576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b
};

struct EFI_DEVICE_PATH_PROTOCOL {
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
};

constexpr EFI_GUID EFI_PC_ANSI_GUID = {
    0xe0c14753, 0xf9be, 0x11d2, 0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d
};

constexpr EFI_GUID EFI_VT_100_GUID = {
    0xdfa66065, 0xb419, 0x11d3, 0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d
};

constexpr EFI_GUID EFI_VT_100_PLUS_GUID = {
    0x7baec70b, 0x57e0, 0x4c76, 0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43
};

constexpr EFI_GUID EFI_VT_UTF8_GUID = {
    0xad15a0d6, 0x8bec, 0x4acf, 0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88
};

constexpr EFI_GUID DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL = {
    0x37499A9D, 0x542F, 0x4C89, 0xA0, 0x26, 0x35, 0xDA, 0x14, 0x20, 0x94, 0xE4
};
