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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

struct EFI_TIME_CAPABILITIES {
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
};

#pragma clang diagnostic pop

using EFI_GET_TIME = EFIAPI EFI_STATUS (*)
(EFI_TIME *Time,
 EFI_TIME_CAPABILITIES *Capabilities);

constexpr UINT8 EFI_TIME_ADJUST_DAYLIGHT = 0x01;
constexpr UINT8 EFI_TIME_IN_DAYLIGHT = 0x02;

constexpr INT16 EFI_UNSPECIFIED_TIMEZONE = 0x07FF;

using EFI_SET_TIME = EFIAPI EFI_STATUS (*)
(EFI_TIME *Time);

using EFI_GET_WAKEUP_TIME = EFIAPI EFI_STATUS (*)
(BOOLEAN *Enabled,
 BOOLEAN *Pending,
 EFI_TIME *Time);

using EFI_SET_WAKEUP_TIME = EFIAPI EFI_STATUS (*)
(BOOLEAN Enable,
 EFI_TIME *Time);
