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

enum EFI_RESET_TYPE
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

using EFI_RESET_SYSTEM = EFIAPI
VOID (*)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize,
         VOID *ResetData);

using EFI_GET_NEXT_HIGH_MONO_COUNT = EFIAPI EFI_STATUS (*)(UINT32 *HighCount);

struct EFI_CAPSULE_BLOCK_DESCRIPTOR
{
    UINT64 Length;
    union
    {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
};

struct EFI_CAPSULE_HEADER
{
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
};

using EFI_UPDATE_CAPSULE = EFIAPI
EFI_STATUS (*)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount,
               EFI_PHYSICAL_ADDRESS ScatterGatherList);

constexpr UINT32 CAPSULE_FLAGS_PERSIST_ACROSS_RESET = 0x00010000;
constexpr UINT32 CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE = 0x00020000;
constexpr UINT32 CAPSULE_FLAGS_INITIATE_RESET = 0x00040000;

using EFI_QUERY_CAPSULE_CAPABILITIES = EFIAPI
EFI_STATUS (*)(EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount,
               UINT64 *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);

constexpr UINT64 EFI_OS_INDICATIONS_BOOT_TO_FW_UI = 0x0000000000000001;
constexpr UINT64 EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION = 0x0000000000000002;
constexpr UINT64 EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED =
    0x0000000000000004;
constexpr UINT64 EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED = 0x0000000000000008;
constexpr UINT64 EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED =
    0x0000000000000010;

constexpr EFI_GUID EFI_CAPSULE_REPORT_GUID = { 0x39b68c46, 0xf7fb, 0x441b, 0xb6,
                                               0xec,       0x16,   0xb0,   0xf6,
                                               0x98,       0x21,   0xf3 };

struct EFI_CAPSULE_RESULT_VARIABLE_HEADER
{
    UINT32 VariableTotalSize;
    UINT32 Reserved; // for alignment
    EFI_GUID CapsuleGuid;
    EFI_TIME CapsuleProcessed;
    EFI_STATUS CaspuleStatus;
};

struct EFI_CAPSULE_RESULT_VARIABLE_FMP
{
    UINT16 Version;
    UINT8 PayloadIndex;
    UINT8 UpdateImageIndex;

    EFI_GUID UpdateImageTypeId;
    // CHAR16 CapsuleFileName[];
    // CHAR16 CapsuleTarget[];
};
