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

constexpr EFI_GUID EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID = {
    0x642cd590, 0x8059, 0x4c0a, 0xa9, 0x58, 0xc5, 0xec, 0x7, 0xd2, 0x3c, 0x4b
};

struct EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;

using EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY = EFIAPI
EFI_STATUS (*)(EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
               EFI_HANDLE ControllerHandle, EFI_HANDLE ChildHandle,
               UINTN *Instance, EFI_GUID **ParameterTypeGuid,
               VOID **ParameterBlock, UINTN *ParameterBlockSize);

enum EFI_PLATFORM_CONFIGURATION_ACTION {
    EfiPlatformConfigurationActionNone,
    EfiPlatformConfigurationActionStopController,
    EfiPlatformConfigurationActionRestartController,
    EfiPlatformConfigurationActionRestartPlatform,
    EfiPlatformConfigurationActionNvramFailed,
    EfiPlatformConfigurationActionMaximum
};

using EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE = EFIAPI
EFI_STATUS (*)(EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
               EFI_HANDLE ControllerHandle, EFI_HANDLE ChildHandle,
               UINTN *Instance, EFI_GUID *ParameterTypeGuid,
               VOID *ParameterBlock, UINTN ParameterBlockSize,
               EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction);

struct EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL {
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY Query;
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE Response;
};

constexpr EFI_GUID EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID = {
    0x345ecc0e, 0xcb6, 0x4b75, 0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e
};

struct EFI_CONFIGURE_CLP_PARAMTER_BLK {
    CHAR8 *CLPCommand;
    UINT32 CLPCommandLength;
    CHAR8 *CLPReturnString;
    UINT32 CLPReturnStringLength;
    UINT8 CLPCmdStatus;
    UINT8 CLPErrorValue;
    UINT16 CLPMsgCode;
};
