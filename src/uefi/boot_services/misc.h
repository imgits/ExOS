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

using EFI_SET_WATCHDOG_TIMER = EFIAPI EFI_STATUS (*)
(UINTN Timeout,
 UINT64 WatchdogCode,
 UINTN DataSize,
 CHAR16 *WatchdogData);

using EFI_STALL = EFIAPI EFI_STATUS (*)
(UINTN Microseconds);

using EFI_COPY_MEM = EFIAPI VOID (*)
(VOID *Destination,
 VOID *Source,
 UINTN Length);

using EFI_SET_MEM = EFIAPI VOID (*)
(VOID *Buffer,
 UINTN Size,
 UINT8 Value);

using EFI_GET_NEXT_MONOTONIC_COUNT = EFIAPI EFI_STATUS (*)
(UINT64 *Count);

using EFI_INSTALL_CONFIGURATION_TABLE = EFIAPI EFI_STATUS (*)
(EFI_GUID *Guid,
 VOID *Table);

using EFI_CALCULATE_CRC32 = EFIAPI EFI_STATUS (*)
(VOID *Data,
 UINTN DataSize,
 UINT32 *Crc32);
