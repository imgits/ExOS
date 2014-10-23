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

#include "paging/paging.h"

#include <cstddef>
#include "paging/structures.h"
#include "registers/registers.h"
#include "uefi/uefi.h"
#include "lib/assert.h"
#include "lib/util.h"
#include "lib/array.h"

namespace {

alignas(Paging::PAGE_SIZE) Array<PageMapLevel4Entry, 512> pml4_table;

void *get_largest_free_memory_region(const Uefi::MemoryMap &map, size_t &limit)
{
    size_t num_pages = 0;
    void *addr = nullptr;

    EFI_MEMORY_DESCRIPTOR *desc = &map.memory_map[0];
    UINTN cnt = map.memory_map_size / map.descriptor_size;

    for (; cnt-->0; inc_ptr_by_num_bytes(desc, map.descriptor_size)) {
        if (desc->Type == EfiConventionalMemory && desc->NumberOfPages > num_pages) {
            num_pages = desc->NumberOfPages;
            addr = reinterpret_cast<void *>(desc->PhysicalStart);
        }

        limit = desc->PhysicalStart / Paging::PAGE_SIZE + desc->NumberOfPages;
    }

    assert(addr != nullptr);

    return addr;
}

} // end anonynmous namespace

void Paging::setup(const Uefi::MemoryMap &map)
{
    size_t max_num_pages;
    void *start = get_largest_free_memory_region(map, max_num_pages);
    PageTableEntry *page_entries = static_cast<decltype(page_entries)>(start);

    for (uint64_t phys = 0, i = 0; i < max_num_pages; ++i, phys += PAGE_SIZE) {
        page_entries[i] = PageTableEntry {
            .physical_page_base_offset = phys >> 12,
            .present = 1,
            .read_write = 1
        };
    }

    const uint64_t end_page_entries = align(max_num_pages, 512);
    const uint64_t num_page_tables = end_page_entries / 512;

    zero_array(&page_entries[max_num_pages], end_page_entries - max_num_pages);

    // -- pages tables done --

    start = align(&page_entries[end_page_entries], PAGE_SIZE);
    PageDirectoryEntry *page_dir_entries = static_cast<decltype(page_dir_entries)>(start);

    for (uint64_t table = 0, i = 0; i < num_page_tables; ++i, table += 512) {
        page_dir_entries[i] = PageDirectoryEntry {
            .page_table_base_offset = reinterpret_cast<uint64_t>(&page_entries[table]) >> 12,
            .present = 1,
            .read_write = 1
        };
    }

    const uint64_t end_page_dir_entries = align(num_page_tables, 512);
    const uint64_t num_page_dir_tables = end_page_dir_entries / 512;

    zero_array(&page_dir_entries[num_page_tables], end_page_dir_entries - num_page_tables);

    // -- page directory tables done --

    start = align(&page_dir_entries[end_page_dir_entries], PAGE_SIZE);
    PageDirectoryPointerEntry *page_dir_ptr_entries = static_cast<decltype(page_dir_ptr_entries)>(start);

    for (uint64_t table = 0, i = 0; i < num_page_dir_tables; ++i, table += 512) {
        page_dir_ptr_entries[i] = PageDirectoryPointerEntry {
            .page_directory_base_offset = reinterpret_cast<uint64_t>(&page_dir_entries[table]) >> 12,
            .present = 1,
            .read_write = 1
        };
    }

    const uint64_t end_page_dir_ptr_entries = align(num_page_dir_tables, 512);
    const uint64_t num_page_dir_ptr_tables = end_page_dir_ptr_entries / 512;

    zero_array(&page_dir_ptr_entries[num_page_dir_tables], end_page_dir_ptr_entries - num_page_dir_tables);

    // -- page directory pointer tables done --

    for (uint64_t table = 0, i = 0; i < num_page_dir_ptr_tables; ++i, table += 512) {
        pml4_table[i] = PageMapLevel4Entry {
            .page_directory_pointer_base_offset = reinterpret_cast<uint64_t>(&page_dir_ptr_entries[table]) >> 12,
            .present = 1,
            .read_write = 1
        };
    }

    // -- pml4 table done --

    Registers::Cr3 cr3 = {
        .page_map_level_4_table_base_address = reinterpret_cast<uint64_t>(&pml4_table[0]) >> 12
    };

    __asm__("mov %[cr3], %%cr3" : : [cr3]"r"(cr3));
}
