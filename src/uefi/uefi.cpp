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

#include "lib/util.h"
#include "asm/asm.h"

EFI_STATUS Uefi::print(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL &conout, const CHAR16 *s)
{
    return conout.OutputString(&conout, const_cast<CHAR16 *>(s));
}

bool Uefi::status_is_error(EFI_STATUS x)
{
    return x & EFI_HIGH_BIT;
}

EFI_STATUS Uefi::get_memory_map(const EFI_BOOT_SERVICES &bs, MemoryMap &map)
{
    map.memory_map_size = 0;

    EFI_STATUS status = bs.GetMemoryMap(&map.memory_map_size, map.memory_map,
                                        &map.map_key, &map.descriptor_size,
                                        &map.descriptor_version);
    if (status_is_error(status) && status != EFI_BUFFER_TOO_SMALL)
        return status;

    do {
        map.memory_map_size *= 2;

        status = bs.AllocatePool(EfiLoaderData, map.memory_map_size,
                                 reinterpret_cast<VOID **>(&map.memory_map));
        if (status_is_error(status))
            return status;

        status = bs.GetMemoryMap(&map.memory_map_size, map.memory_map,
                                 &map.map_key, &map.descriptor_size,
                                 &map.descriptor_version);
        if (status_is_error(status) && status != EFI_BUFFER_TOO_SMALL)
            return status;
    } while (status == EFI_BUFFER_TOO_SMALL);

    return EFI_SUCCESS;
}

Maybe<Acpi::Rsdp &> Uefi::get_acpi_rsdp(const EFI_SYSTEM_TABLE &systab)
{
    const EFI_GUID acpi = EFI_ACPI_TABLE_GUID;

    for (UINTN i = 0; i < systab.NumberOfTableEntries; ++i)
        if (are_memory_equal(systab.ConfigurationTable[i].VendorGuid, acpi))
            return *static_cast<Acpi::Rsdp *>(systab.ConfigurationTable[i].VendorTable);

    return None();
}

EFI_STATUS Uefi::get_gop(EFI_HANDLE handle, const EFI_BOOT_SERVICES &bs,
                         EFI_GRAPHICS_OUTPUT_PROTOCOL *&gop)
{
    gop = nullptr;

    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    UINTN num = 0;
    EFI_HANDLE *handles = nullptr;

    EFI_STATUS status = bs.LocateHandleBuffer(ByProtocol, &gop_guid, nullptr,
                                              &num, &handles);
    if (status_is_error(status))
        return status;

    for (UINTN i = 0; i < num; ++i) {
        status = bs.OpenProtocol(handles[i], &gop_guid,
                                 reinterpret_cast<VOID **>(&gop), handle,
                                 nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
        if (status_is_error(status))
            return status;

        switch (gop->Mode->Info->PixelFormat) {
        case PixelBlueGreenRedReserved8BitPerColor:
        case PixelRedGreenBlueReserved8BitPerColor:
            return EFI_SUCCESS;
        case PixelBltOnly:
        case PixelBitMask:
        case PixelFormatMax:
            break;
        }
    }

    return EFI_SUCCESS;
}

const CHAR16 *Uefi::status_to_string(EFI_STATUS status)
{
    switch (status) {
    case EFI_SUCCESS:               return u"Success";
    case EFI_LOAD_ERROR:            return u"Load error";
    case EFI_INVALID_PARAMETER:     return u"Invalid parameter";
    case EFI_UNSUPPORTED:           return u"Unsupported";
    case EFI_BAD_BUFFER_SIZE:       return u"Bad buffer size";
    case EFI_BUFFER_TOO_SMALL:      return u"Buffer too small";
    case EFI_NOT_READY:             return u"Not ready";
    case EFI_DEVICE_ERROR:          return u"Device error";
    case EFI_WRITE_PROTECTED:       return u"Write protected";
    case EFI_OUT_OF_RESOURCES:      return u"Out of resources";
    case EFI_VOLUME_CORRUPTED:      return u"Volume corrupted";
    case EFI_VOLUME_FULL:           return u"Volume full";
    case EFI_NO_MEDIA:              return u"No media";
    case EFI_MEDIA_CHANGED:         return u"Media changed";
    case EFI_NOT_FOUND:             return u"Not found";
    case EFI_ACCESS_DENIED:         return u"Access denied";
    case EFI_NO_RESPONSE:           return u"No response";
    case EFI_NO_MAPPING:            return u"No mapping";
    case EFI_TIMEOUT:               return u"Timeout";
    case EFI_NOT_STARTED:           return u"Not started";
    case EFI_ALREADY_STARTED:       return u"Already started";
    case EFI_ABORTED:               return u"Aborted";
    case EFI_ICMP_ERROR:            return u"ICMP error";
    case EFI_TFTP_ERROR:            return u"TFTP error";
    case EFI_PROTOCOL_ERROR:        return u"Protocol error";
    case EFI_INCOMPATIBLE_VERSION:  return u"Incompatible version";
    case EFI_SECURITY_VIOLATION:    return u"Security violation";
    case EFI_CRC_ERROR:             return u"CRC error";
    case EFI_END_OF_MEDIA:          return u"End of media";
    case EFI_END_OF_FILE:           return u"End of file";
    case EFI_INVALID_LANGUAGE:      return u"Invalid language";
    case EFI_COMPROMISED_DATA:      return u"Compromised data";
    case EFI_IP_ADDRESS_CONFLICT:   return u"IP address conflict";
    case EFI_WARN_UNKNOWN_GLYPH:    return u"Unknown glyph";
    case EFI_WARN_DELETE_FAILURE:   return u"Delete failure";
    case EFI_WARN_WRITE_FAILURE:    return u"Write failure";
    case EFI_WARN_BUFFER_TOO_SMALL: return u"Buffer too small";
    case EFI_WARN_STALE_DATA:       return u"Stale data";
    }
}

void Uefi::die(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL &conout, EFI_STATUS status,
               const CHAR16 *s)
{
    print(conout, s);
    print(conout, u": ");
    print(conout, status_to_string(status));
    print(conout, u"\r\n");
    Asm::hlt();
}

StringRef Uefi::memory_type_to_string(EFI_MEMORY_TYPE type)
{
    switch (type) {
    case EfiReservedMemoryType:         return "Reserved"_s;
    case EfiLoaderCode:                 return "Loader Code"_s;
    case EfiLoaderData:                 return "Loader Data"_s;
    case EfiBootServicesCode:           return "Boot Services Code"_s;
    case EfiBootServicesData:           return "Boot Services Data"_s;
    case EfiRuntimeServicesCode:        return "Runtime Services Code"_s;
    case EfiRuntimeServicesData:        return "Runtime Services Data"_s;
    case EfiConventionalMemory:         return "Conventional Memory"_s;
    case EfiUnusableMemory:             return "Unusable Memory"_s;
    case EfiACPIReclaimMemory:          return "ACPI Reclaim Memory"_s;
    case EfiACPIMemoryNVS:              return "ACPI Memory NVS"_s;
    case EfiMemoryMappedIO:             return "Memory-Mapped I/O"_s;
    case EfiMemoryMappedIOPortSpace:    return "Memory-Mapped I/O Port Space"_s;
    case EfiPalCode:                    return "Pal Code"_s;
    case EfiMaxMemoryType:              return "Max"_s;
    }
}
