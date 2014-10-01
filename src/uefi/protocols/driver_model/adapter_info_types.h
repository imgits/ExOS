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

constexpr EFI_GUID EFI_ADAPTER_INFO_MEDIA_STATE_GUID =
{ 0xD7C74207, 0xA831, 0x4A26, 0xB1,0xF5,0xD1,0x93,0x06,0x5C,0xE8,0xB6 };

struct EFI_ADAPTER_INFO_MEDIA_STATES {
    EFI_STATUS MediaStates;
};

constexpr EFI_GUID EFI_ADAPTER_INFO_NETWORK_BOOT_GUID =
{ 0x1FBD2960, 0x4130, 0x41E5, 0x94,0xAC,0xD2, 0xCF, 0x03, 0x7F, 0xB3, 0x7C };

struct EFI_ADAPTER_INFO_NETWORK_BOOT {
    BOOLEAN iSsciIpv4BootCapablity;
    BOOLEAN iScsiIpv6BootCapablity;
    BOOLEAN FCoeBootCapablity;
    BOOLEAN OffloadCapability;
    BOOLEAN iScsiMpioCapability
    BOOLEAN iScsiIpv4Boot;
    BOOLEAN iScsiIpv6Boot;
    BOOLEAN FCoeBoot;
};

constexpr EFI_GUID EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID =
{ 0x114da5ef, 0x2cf1, 0x4e12, 0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x5, 0xd9 };

struct EFI_ADAPTER_INFO_SAN_MAC_ADDRESS {
    EFI_MAC_ADDRESS SanMacAddress;
};
