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

constexpr EFI_GUID EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID = {
    0x4d330321, 0x025f, 0x4aac, 0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63
};

struct EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

enum EFI_DRIVER_DIAGNOSTIC_TYPE {
    EfiDriverDiagnosticTypeStandard,
    EfiDriverDiagnosticTypeExtended,
    EfiDriverDiagnosticTypeManufacturing,
    EfiDriverDiagnosticTypeCancel,
    EfiDriverDiagnosticTypeMaximum
};

using EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS = EFIAPI
EFI_STATUS (*)(EFI_DRIVER_DIAGNOSTICS2_PROTOCOL *This,
               EFI_HANDLE ControllerHandle, EFI_HANDLE ChildHandle,
               EFI_DRIVER_DIAGNOSTIC_TYPE DiagnosticType, CHAR8 *Language,
               EFI_GUID **ErrorType, UINTN *BufferSize, CHAR16 **Buffer);

struct EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
    EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS RunDiagnostics;
    CHAR8 *SupportedLanguages;
};
