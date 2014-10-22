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

#include <cstdint>

struct VirtualAddress {
    uint64_t physical_page_offset : 12;
    uint64_t page_table_offset : 9;
    uint64_t page_directory_offset : 9;
    uint64_t page_directory_pointer_offset : 9;
    uint64_t page_map_level4_offset : 9;
    uint64_t sign_extend : 16;
};

struct PageMapLevel4Entry {
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_level_writethrough : 1;
    uint64_t page_level_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t ignored : 1;
    uint64_t mbz : 1;
    uint64_t avl : 4;
    uint64_t page_directory_pointer_base_offset : 40;
    uint64_t available : 11;
    uint64_t no_execute : 1;
};

struct PageDirectoryPointerEntry {
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_level_writethrough : 1;
    uint64_t page_level_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t ignored : 1;
    uint64_t zero : 1;
    uint64_t avl : 4;
    uint64_t page_directory_base_offset : 40;
    uint64_t available : 11;
    uint64_t no_execute : 1;
};

struct PageDirectoryEntry {
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_level_writethrough : 1;
    uint64_t page_level_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t ignored : 1;
    uint64_t mbz : 1;
    uint64_t avl : 4;
    uint64_t page_table_base_offset : 40;
    uint64_t available : 11;
    uint64_t no_execute : 1;
};

struct PageTableEntry {
    uint64_t present : 1;
    uint64_t read_write : 1;
    uint64_t user_supervisor : 1;
    uint64_t page_level_writethrough : 1;
    uint64_t page_level_cache_disable : 1;
    uint64_t accessed : 1;
    uint64_t dirty : 1;
    uint64_t page_attribute_table : 1;
    uint64_t global_page : 1;
    uint64_t avl : 3;
    uint64_t physical_page_base_offset : 40;
    uint64_t available : 11;
    uint64_t no_execute : 1;
};
