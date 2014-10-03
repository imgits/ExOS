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

constexpr EFI_GUID EFI_ABSOLUTE_POINTER_PROTOCOL_GUID = {
    0x8D59D32B, 0xC655, 0x4AE9, 0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43
};

struct EFI_ABSOLUTE_POINTER_MODE
{
    UINT64 AbsoluteMinX;
    UINT64 AbsoluteMinY;
    UINT64 AbsoluteMinZ;
    UINT64 AbsoluteMaxX;
    UINT64 AbsoluteMaxY;
    UINT64 AbsoluteMaxZ;
    UINT32 Attributes;
};

constexpr UINT32 EFI_ABSP_SupportsAltActive = 0x00000001;
constexpr UINT32 EFI_ABSP_SupportsPressureAsZ = 0x00000002;

struct EFI_ABSOLUTE_POINTER_PROTOCOL;

using EFI_ABSOLUTE_POINTER_RESET = EFIAPI
EFI_STATUS (*)(EFI_ABSOLUTE_POINTER_PROTOCOL *This,
               BOOLEAN ExtendedVerification);

struct EFI_ABSOLUTE_POINTER_STATE
{
    UINT64 CurrentX;
    UINT64 CurrentY;
    UINT64 CurrentZ;
    UINT32 ActiveButtons;
};

using EFI_ABSOLUTE_POINTER_GET_STATE = EFIAPI
EFI_STATUS (*)(EFI_ABSOLUTE_POINTER_PROTOCOL *This,
               EFI_ABSOLUTE_POINTER_STATE *State);

constexpr UINT32 EFI_ABSP_TouchActive = 0x00000001;
constexpr UINT32 EFI_ABS_AltActive = 0x00000002;

struct EFI_ABSOLUTE_POINTER_PROTOCOL
{
    EFI_ABSOLUTE_POINTER_RESET Reset;
    EFI_ABSOLUTE_POINTER_GET_STATE GetSate;
    EFI_EVENT WaitForInput;
    EFI_ABSOLUTE_POINTER_MODE *Mode;
};
