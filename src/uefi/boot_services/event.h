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

using EFI_EVENT_NOTIFY = EFIAPI VOID (*)(EFI_EVENT Event, VOID *Context);

using EFI_TPL = UINTN;

using EFI_CREATE_EVENT = EFIAPI
EFI_STATUS (*)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction,
               VOID *NotifyContext, EFI_EVENT *Event);

constexpr UINT64 EVT_TIMER = 0x80000000;
constexpr UINT64 EVT_RUNTIME = 0x40000000;
constexpr UINT64 EVT_NOTIFY_WAIT = 0x00000100;
constexpr UINT64 EVT_NOTIFY_SIGNAL = 0x00000200;
constexpr UINT64 EVT_SIGNAL_EXIT_BOOT_SERVICES = 0x00000201;
constexpr UINT64 EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE = 0x60000202;

using EFI_CREATE_EVENT_EX = EFIAPI
EFI_STATUS (*)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction,
               const VOID *NotifyContext, const EFI_GUID *EventGuid,
               EFI_EVENT *Event);

constexpr EFI_GUID EFI_EVENT_GROUP_EXIT_BOOT_SERVICES = {
    0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf
};

constexpr EFI_GUID EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE = {
    0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96
};

constexpr EFI_GUID EFI_EVENT_GROUP_MEMORY_MAP_CHANGE = {
    0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab
};

constexpr EFI_GUID EFI_EVENT_GROUP_READY_TO_BOOT = {
    0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0xd, 0x2b
};

using EFI_CLOSE_EVENT = EFIAPI EFI_STATUS (*)(EFI_EVENT Event);

using EFI_SIGNAL_EVENT = EFIAPI EFI_STATUS (*)(EFI_EVENT Event);

using EFI_WAIT_FOR_EVENT = EFIAPI
EFI_STATUS (*)(UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);

using EFI_CHECK_EVENT = EFIAPI EFI_STATUS (*)(EFI_EVENT Event);

enum EFI_TIMER_DELAY
{
    TimerCancel,
    TimerPeriodic,
    TimerRelative
};

using EFI_SET_TIMER = EFIAPI
EFI_STATUS (*)(EFI_EVENT Event, EFI_TIMER_DELAY Type, UINT64 TriggerTime);

using EFI_RAISE_TPL = EFIAPI EFI_TPL (*)(EFI_TPL NewTpl);

constexpr EFI_TPL TPL_APPLICATION = 4;
constexpr EFI_TPL TPL_CALLBACK = 8;
constexpr EFI_TPL TPL_NOTIFY = 16;
constexpr EFI_TPL TPL_HIGH_LEVEL = 31;

using EFI_RESTORE_TPL = EFIAPI VOID (*)(EFI_TPL OldTpl);
