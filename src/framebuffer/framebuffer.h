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

#include "lib/immut_array_ref.h"

struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

namespace Framebuffer {

// Currently accepted colors.
enum class Color {
    BLACK,
    WHITE,
    RED,
    LIME,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    SILVER,
    GRAY,
    MAROON,
    OLIVE,
    GREEN,
    PURPLE,
    TEAL,
    NAVY
};

// Initializes the framebuffer. You must call this before calling any other
// framebuffer function.
void init(const EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE &gop_mode);

// Redraws the entire screen in the current background color.
void clear_screen();

void set_foreground_color(Color color);

void set_background_color(Color color);

void put_char(char c);

void put_string(StringRef x);

} // namespace Framebuffer end
