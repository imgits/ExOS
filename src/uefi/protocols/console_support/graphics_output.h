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

constexpr EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID = {
    0x9042a9de, 0x23dc, 0x4a38, 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a
};

struct EFI_PIXEL_BITMASK
{
    UINT32 RedMask;
    UINT32 GreenMask;
    UINT32 BlueMask;
    UINT32 ReservedMask;
};

enum EFI_GRAPHICS_PIXEL_FORMAT
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
};

struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    UINT32 PixelsPerScanLine;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE
{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    UINTN FrameBufferSize;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

using EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE = EFIAPI
EFI_STATUS (*)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber,
               UINTN *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);

using EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE = EFIAPI
EFI_STATUS (*)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNUmber);

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL
{
    UINT8 Blue;
    UINT8 Green;
    UINT8 Red;
    UINT8 Reserved;
};

enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION
{
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
};

using EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT = EFIAPI
EFI_STATUS (*)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
               EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
               EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX,
               UINTN SourceY, UINTN DestinationX, UINTN DestinationY,
               UINTN Width, UINTN Height, UINTN Delta);

struct EFI_GRAPHICS_OUTPUT_PROTOCOL
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

constexpr EFI_GUID EFI_EDID_DISCOVERED_PROTOCOL_GUID = {
    0x1c0c34f6, 0xd380, 0x41fa, 0xa0, 0x49, 0x8a, 0xd0, 0x6c, 0x1a, 0x66, 0xaa
};

struct EFI_EDID_DISCOVERED_PROTOCOL
{
    UINT32 SizeOfEdid;
    UINT8 *Edid;
};

constexpr EFI_GUID EFI_EDID_ACTIVE_PROTOCOL_GUID = {
    0xbd8c1056, 0x9f36, 0x44ec, 0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86
};

struct EFI_EDID_ACTIVE_PROTOCOL
{
    UINT32 SizeOFEdid;
    UINT8 *Edid;
};

constexpr EFI_GUID EFI_EDID_OVERRIDE_PROTOCOL_GUID = {
    0x48ecb431, 0xfb72, 0x45c0, 0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x4, 0xb, 0xd5
};

struct EFI_EDID_OVERRIDE_PROTOCOL;

using EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID = EFIAPI
EFI_STATUS (*)(EFI_EDID_OVERRIDE_PROTOCOL *This, EFI_HANDLE *ChildHandle,
               UINT32 *Attributes, UINTN *EdidSize, UINT8 **Edid);

constexpr UINT32 EFI_EDID_OVERRIDE_DONT_OVERRIDE = 0x01;
constexpr UINT32 EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG = 0x02;

struct EFI_EDID_OVERRIDE_PROTOCOL
{
    EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID GetEdid;
};
