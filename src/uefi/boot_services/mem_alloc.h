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

enum EFI_ALLOCATE_TYPE {
    AllocateAnyPages,
    AllocateMaxAddress,
    MaxAllocateType
};

using EFI_ALLOCATE_PAGES = EFIAPI EFI_STATUS (*)
(EFI_ALLOCATE_TYPE Type,
 EFI_MEMORY_TYPE MemoryType,
 UINTN Pages,
 EFI_PHYSICAL_ADDRESS *Memory);

using EFI_FREE_PAGES = EFIAPI EFI_STATUS (*)
(EFI_PHYSICAL_ADDRESS Memory,
 UINTN Pages);

constexpr UINT64 EFI_MEMORY_UC = 0x0000000000000001;
constexpr UINT64 EFI_MEMORY_WC = 0x0000000000000002;
constexpr UINT64 EFI_MEMORY_WT = 0x0000000000000004;
constexpr UINT64 EFI_MEMORY_WB = 0x0000000000000008;
constexpr UINT64 EFI_MEMORY_UCE = 0x0000000000000010;
constexpr UINT64 EFI_MEMORY_WP = 0x0000000000001000;
constexpr UINT64 EFI_MEMORY_RP = 0x0000000000002000;
constexpr UINT64 EFI_MEMORY_XP = 0x0000000000004000;
constexpr UINT64 EFI_MEMORY_RUNTIME = 0x8000000000000000;

constexpr UINT32 EFI_MEMORY_DESCRIPTOR_VERSION = 1;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"

struct EFI_MEMORY_DESCRIPTOR {
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
};

#pragma clang diagnostic pop

using EFI_GET_MEMORY_MAP = EFIAPI EFI_STATUS (*)
(UINTN *MemoryMapSize,
 EFI_MEMORY_DESCRIPTOR *MemoryMap,
 UINTN *MapKey,
 UINTN *DescriptorSize,
 UINT32 *DescriptorVersion);

using EFI_ALLOCATE_POOL = EFIAPI EFI_STATUS (*)
(EFI_MEMORY_TYPE PoolType,
 UINTN Size,
 VOID **Buffer);

using EFI_FREE_POOL = EFIAPI EFI_STATUS (*)
(VOID *Buffer);
