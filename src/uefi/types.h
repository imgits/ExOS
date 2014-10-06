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

/*
 * UEFI data types. See UEFI spec. 2.3.1.
 */

#include <cstdint>

#define EFIAPI __attribute__((ms_abi))
#define CONST const

using BOOLEAN = uint8_t;
constexpr BOOLEAN FALSE = 0;
constexpr BOOLEAN TRUE = 1;
using INTN = int64_t;
using UINTN = uint64_t;
using INT8 = int8_t;
using UINT8 = uint8_t;
using INT16 = int16_t;
using UINT16 = uint16_t;
using INT32 = int32_t;
using UINT32 = uint32_t;
using INT64 = int64_t;
using UINT64 = uint64_t;
using CHAR8 = char;
static_assert(sizeof(char16_t) == 2, "char16_t is not 16-bits!");
using CHAR16 = char16_t;
using VOID = void;
using EFI_HANDLE = VOID *;
using EFI_EVENT = VOID *;
using EFI_PHYSICAL_ADDRESS = UINT64;
using EFI_VIRTUAL_ADDRESS = UINT64;

struct EFI_GUID
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4;
    UINT8 Data5;
    UINT8 Data6;
    UINT8 Data7;
    UINT8 Data8;
    UINT8 Data9;
    UINT8 Data11;
    UINT8 Data12;
};

enum EFI_MEMORY_TYPE
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
};

struct EFI_TIME
{
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    INT16 TimeZone;
    UINT8 Daylight;
    UINT8 Pad2;
};

struct EFI_INPUT_KEY
{
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
};

constexpr UINT64 EFI_HIGH_BIT = 0x8000000000000000;

constexpr UINT64 efi_val_to_err(UINT64 x)
{
    return x | EFI_HIGH_BIT;
}

enum EFI_STATUS : UINTN
{
    EFI_SUCCESS                 = 0,

    EFI_LOAD_ERROR              = efi_val_to_err(1),
    EFI_INVALID_PARAMETER       = efi_val_to_err(2),
    EFI_UNSUPPORTED             = efi_val_to_err(3),
    EFI_BAD_BUFFER_SIZE         = efi_val_to_err(4),
    EFI_BUFFER_TOO_SMALL        = efi_val_to_err(5),
    EFI_NOT_READY               = efi_val_to_err(6),
    EFI_DEVICE_ERROR            = efi_val_to_err(7),
    EFI_WRITE_PROTECTED         = efi_val_to_err(8),
    EFI_OUT_OF_RESOURCES        = efi_val_to_err(9),
    EFI_VOLUME_CORRUPTED        = efi_val_to_err(10),
    EFI_VOLUME_FULL             = efi_val_to_err(11),
    EFI_NO_MEDIA                = efi_val_to_err(12),
    EFI_MEDIA_CHANGED           = efi_val_to_err(13),
    EFI_NOT_FOUND               = efi_val_to_err(14),
    EFI_ACCESS_DENIED           = efi_val_to_err(15),
    EFI_NO_RESPONSE             = efi_val_to_err(16),
    EFI_NO_MAPPING              = efi_val_to_err(17),
    EFI_TIMEOUT                 = efi_val_to_err(18),
    EFI_NOT_STARTED             = efi_val_to_err(19),
    EFI_ALREADY_STARTED         = efi_val_to_err(20),
    EFI_ABORTED                 = efi_val_to_err(21),
    EFI_ICMP_ERROR              = efi_val_to_err(22),
    EFI_TFTP_ERROR              = efi_val_to_err(23),
    EFI_PROTOCOL_ERROR          = efi_val_to_err(24),
    EFI_INCOMPATIBLE_VERSION    = efi_val_to_err(25),
    EFI_SECURITY_VIOLATION      = efi_val_to_err(26),
    EFI_CRC_ERROR               = efi_val_to_err(27),
    EFI_END_OF_MEDIA            = efi_val_to_err(28),
    EFI_END_OF_FILE             = efi_val_to_err(31),
    EFI_INVALID_LANGUAGE        = efi_val_to_err(32),
    EFI_COMPROMISED_DATA        = efi_val_to_err(33),
    EFI_IP_ADDRESS_CONFLICT     = efi_val_to_err(34),

    EFI_WARN_UNKNOWN_GLYPH      = 1,
    EFI_WARN_DELETE_FAILURE     = 2,
    EFI_WARN_WRITE_FAILURE      = 3,
    EFI_WARN_BUFFER_TOO_SMALL   = 4,
    EFI_WARN_STALE_DATA         = 5
};
