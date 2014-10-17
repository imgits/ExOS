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

using EFI_GET_VARIABLE = EFIAPI
EFI_STATUS (*)(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 *Attributes,
               UINTN *DataSize, VOID *Data);

constexpr UINT32 EFI_VARIABLE_NON_VOLATILE = 0x00000001;
constexpr UINT32 EFI_VARIABLE_BOOTSERVICE_ACCESS = 0x00000002;
constexpr UINT32 EFI_VARIABLE_RUNTIME_ACCESS = 0x00000004;
constexpr UINT32 EFI_VARIABLE_HARDWARE_ERROR_RECORD = 0x00000008;
constexpr UINT32 EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS = 0x00000010;
constexpr UINT32 EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS =
    0x00000020;
constexpr UINT32 EFI_VARIABLE_APPEND_WRITE = 0x00000040;

using EFI_GET_NEXT_VARIABLE_NAME = EFIAPI
EFI_STATUS (*)(UINTN *VariableNameSize, CHAR16 *VariableName,
               EFI_GUID VendorGuid);

using EFI_SET_VARIABLE = EFIAPI
EFI_STATUS (*)(CHAR16 *VariableName, EFI_GUID *VendorGuid, UINT32 Attributes,
               UINTN DataSize, VOID *Data);

struct WIN_CERTIFICATE {
    UINT32 dwLength;
    UINT16 wRevision;
    UINT16 wCertificateType;
    // UINT8 bCertificate[ANYSIZE_ARRAY]
};

struct WIN_CERTIFICATE_UEFI_GUID {
    WIN_CERTIFICATE Hdr;
    EFI_GUID CertType;
    // UINT8 CertData[ANYSIZE_ARRAY];
};

struct EFI_VARIABLE_AUTHENTICATION {
    UINT64 MonotonicCount;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
};

struct EFI_VARIABLE_AUTHENTICATION_2 {
    EFI_TIME TimeStamp;
    WIN_CERTIFICATE_UEFI_GUID AuthInfo;
};

using EFI_QUERY_VARIABLE_INFO = EFIAPI
EFI_STATUS (*)(UINT32 Attributes, UINT64 *MaximumVariableStorageSize,
               UINT64 *RemainingVariableStorageSize,
               UINT64 *MaximumVariableSize);
