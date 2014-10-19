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

#include "uefi/uefi.h"
#include "framebuffer/framebuffer.h"
#include "lib/printf.h"
#include "cpuid/cpuid.h"
#include "asm/asm.h"
#include "segmentation/gdt.h"
#include "segmentation/idt.h"

extern "C" EFI_STATUS kmain(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab) EFIAPI;

// Shares its definition with the symbol in uefi/uefi.h
const EFI_RUNTIME_SERVICES *Uefi::g_runtime;

EFI_STATUS kmain(EFI_HANDLE handle, EFI_SYSTEM_TABLE *systab)
{
    Uefi::g_runtime = systab->RuntimeServices;

    const EFI_BOOT_SERVICES &bs = *systab->BootServices;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL &conout = *systab->ConOut;

    EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
    EFI_STATUS status = Uefi::get_gop(handle, bs, gop);
    if (Uefi::status_is_error(status))
        Uefi::die(conout, status, u"Trying to get GOP");
    if (gop == nullptr)
        Uefi::g_runtime->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, nullptr);

    Framebuffer::init(*gop->Mode);

    Framebuffer::clear_screen();

    Uefi::MemoryMap memory_map;
    status = Uefi::get_memory_map(bs, memory_map);
    if (Uefi::status_is_error(status))
        Uefi::die(conout, status, u"Trying to get memory map");

    status = bs.ExitBootServices(handle, memory_map.map_key);
    if (Uefi::status_is_error(status))
        Uefi::die(conout, status, u"ExitBootServices()");

    Gdt::setup();

    Idt::setup();

    printf("Welcome! [CPU: ()]\n\n"_cts, Cpuid::get_vendor_string().ref());

    printf("Testing if interrupts are working ((dividing by zero)...\n\n"_cts);

    volatile int x = 0;
    volatile int y = 42 / x;
    (void)y;

    __builtin_unreachable();
}
