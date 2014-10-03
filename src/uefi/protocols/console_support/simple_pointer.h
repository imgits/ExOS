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

constexpr EFI_GUID EFI_SIMPLE_POINTER_PROTOCOL_GUID = {
    0x31878c87, 0xb75, 0x11d5, 0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d
};

struct EFI_SIMPLE_POINTER_MODE
{
    UINT64 ResolutionX;
    UINT64 ResolutionY;
    UINT64 ResolutionZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
};

struct EFI_SIMPLE_POINTER_PROTOCOL;

using EFI_SIMPLE_POINTER_RESET = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_POINTER_PROTOCOL *This, BOOLEAN ExtendedVerification);

struct EFI_SIMPLE_POINTER_STATE
{
    INT32 RelativeMovementX;
    INT32 RelativeMovementY;
    INT32 RelativeMovementZ;
    BOOLEAN LeftButton;
    BOOLEAN RightButton;
};

using EFI_SIMPLE_POINTER_GET_STATE = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_POINTER_PROTOCOL *This,
               EFI_SIMPLE_POINTER_STATE *State);

struct EFI_SIMPLE_POINTER_PROTOCOL
{
    EFI_SIMPLE_POINTER_RESET Reset;
    EFI_SIMPLE_POINTER_GET_STATE GetState;
    EFI_EVENT WaitForInput;
    EFI_SIMPLE_POINTER_MODE *Mode;
};
