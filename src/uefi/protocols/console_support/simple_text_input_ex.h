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

constexpr EFI_GUID EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID = {
    0xdd9e7534, 0x7762, 0x4698, 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa
};

struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;

using EFI_INPUT_RESET_EX = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
               BOOLEAN ExtendedVerification);

using EFI_KEY_TOGGLE_STATE = UINT8;

constexpr EFI_KEY_TOGGLE_STATE EFI_TOGGLE_STATE_VALID = 0x80;
constexpr EFI_KEY_TOGGLE_STATE EFI_KEY_STATE_EXPOSED = 0x40;
constexpr EFI_KEY_TOGGLE_STATE EFI_SCROLL_LOCK_ACTIVE = 0x01;
constexpr EFI_KEY_TOGGLE_STATE EFI_NUM_LOCK_ACTIVE = 0x02;
constexpr EFI_KEY_TOGGLE_STATE EFI_CAPS_LOCK_ACTIVE = 0x04;

struct EFI_KEY_STATE {
    UINT32 KeyShiftState;
    EFI_KEY_TOGGLE_STATE KeyToggleState;
};

constexpr UINT32 EFI_SHIFT_STATE_VALID = 0x80000000;
constexpr UINT32 EFI_RIGHT_SHIFT_PRESSED = 0x00000001;
constexpr UINT32 EFI_LEFT_SHIFT_PRESSED = 0x00000002;
constexpr UINT32 EFI_RIGHT_CONTROL_PRESSED = 0x00000004;
constexpr UINT32 EFI_LEFT_CONTROL_PRESSED = 0x00000008;
constexpr UINT32 EFI_RIGHT_ALT_PRESSED = 0x00000010;
constexpr UINT32 EFI_LEFT_ALT_PRESSED = 0x00000020;
constexpr UINT32 EFI_RIGHT_LOGO_PRESSED = 0x00000040;
constexpr UINT32 EFI_LEFT_LOGO_PRESSED = 0x00000080;
constexpr UINT32 EFI_MENU_KEY_PRESSED = 0x00000100;
constexpr UINT32 EFI_SYS_REQ_PRESSED = 0x00000200;

struct EFI_KEY_DATA {
    EFI_INPUT_KEY Key;
    EFI_KEY_STATE KeyState;
};

using EFI_INPUT_READ_KEY_EX = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This, EFI_KEY_DATA *KeyData);

using EFI_SET_STATE = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
               EFI_KEY_TOGGLE_STATE *KeyToggleState);

using EFI_KEY_NOTIFY_FUNCTION = EFIAPI EFI_STATUS (*)(EFI_KEY_DATA *KeyData);

using EFI_REGISTER_KEYSTROKE_NOTIFY = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This, EFI_KEY_DATA *KeyData,
               EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
               VOID **NotifyHandle);

using EFI_UNREGISTER_KEYSTROKE_NOTIFY = EFIAPI
EFI_STATUS (*)(EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,
               VOID *NotificationHandle);

struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
    EFI_INPUT_RESET_EX Reset;
    EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
    EFI_EVENT WaitForKeyEx;
    EFI_SET_STATE SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};
