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

struct EFI_DEVICE_PATH_PROTOCOL;

using EFI_IMAGE_LOAD = EFIAPI
EFI_STATUS (*)(BOOLEAN BootPolicy, EFI_HANDLE ParentImageHandle,
               EFI_DEVICE_PATH_PROTOCOL *DevicePath, VOID *SourceBuffer,
               UINTN SourceSize, EFI_HANDLE *ImageHandle);

constexpr EFI_GUID EFI_HII_PACKAGE_LIST_PROTOCOL_GUID = {
    0x6a1ee763, 0xd47a, 0x43b4, 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc
};

struct EFI_HII_PACKAGE_LIST_HEADER;
using EFI_HII_PACKAGE_LIST_PROTOCOL = EFI_HII_PACKAGE_LIST_HEADER *;

using EFI_IMAGE_START = EFIAPI
EFI_STATUS (*)(EFI_HANDLE ImageHandle, UINTN *ExitDataSize, CHAR16 **ExitData);

using EFI_IMAGE_UNLOAD = EFIAPI EFI_STATUS (*)(EFI_HANDLE ImageHandle);

struct EFI_SYSTEM_TABLE;

using EFI_IMAGE_ENTRY_POINT = EFIAPI
EFI_STATUS (*)(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable);

using EFI_EXIT = EFIAPI
EFI_STATUS (*)(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus,
               UINTN ExitDataSize, CHAR16 *ExitData);

using EFI_EXIT_BOOT_SERVICES = EFIAPI
EFI_STATUS (*)(EFI_HANDLE ImageHandle, UINTN MapKey);
