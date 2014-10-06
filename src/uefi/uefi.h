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

#include "uefi/systab.h"
#include "uefi/protocols/console_support/all.h"

#include "lib/immut_array_ref.h"
#include "lib/either.h"
#include "lib/maybe.h"

namespace Acpi
{
struct rsdp;
}

namespace Uefi
{

// Prints the string @s using @conout.
EFI_STATUS print(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL &conout, StringRefUefi s);

// Returns true if x is an error status.
bool status_is_error(EFI_STATUS x);

struct MemoryMap
{
    UINTN memory_map_size;
    EFI_MEMORY_DESCRIPTOR *memory_map;
    UINTN map_key;
    UINTN descriptor_size;
    UINT32 descriptor_version;
    char __pad[4];
};

// If it returns EFI_SUCCESS, @map will hold the current memory map.
EFI_STATUS get_memory_map(EFI_BOOT_SERVICES const &bs, MemoryMap &map);

// Either returns a pointer to the ACPI RSDP table if found, or NULL.
Acpi::rsdp *get_acpi_rsdp(EFI_SYSTEM_TABLE const &systab);

// Returns the first instance of a GOP that supports RGB or BGR.
// If no suitable GOP was found, gop will be NULL, and either EFI_SUCCESS or
// an error code will be returned, depending on whether the failure to retrieve
// a GOP was due to an UEFI function or not.
EFI_STATUS get_gop(EFI_HANDLE handle, EFI_BOOT_SERVICES const &bs,
                   EFI_GRAPHICS_OUTPUT_PROTOCOL *&gop);

// Translates @status into a string representation residing in static memory.
StringRefUefi status_to_string(EFI_STATUS status);

// Prints "@s: 'status translated to string'\n" and then halts.
[[noreturn]] void die(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL &conout,
                      EFI_STATUS status, StringRefUefi s);

} // namespace Uefi end
