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

#include <cstdint>
#include <cstddef>

#include "framebuffer/framebuffer.h"

#include "font/font.h"

#include "uefi/protocols/console_support/graphics_output.h"

#include "lib/util.h"

namespace
{

// Framebuffer start address
std::uint32_t *g_framebuffer;

// Size of the framebuffer in bytes
std::size_t g_framebuffer_size;

// max visible horizontal pixels
unsigned int g_max_width;
// max vertical pixels
unsigned int g_max_height;
// actual amount of horizontal pixels
unsigned int g_pixels_per_scan_line;

unsigned int g_current_width;
unsigned int g_current_height;

// amount of pixels of one font line
std::size_t g_font_line_size;

// height of the last column which can display the full font height
unsigned int g_last_font_column;

Framebuffer::Color g_current_bg_color;
Framebuffer::Color g_current_fg_color;

std::uint32_t g_color_array[to_underlying_type(Framebuffer::Color::NAVY) + 1];

// Move every line until the current one up, make current row blank
void scroll()
{
    std::size_t const limit = g_current_height * g_pixels_per_scan_line;

    for (std::size_t i = 0; i < limit; ++i)
        g_framebuffer[i] = g_framebuffer[i + g_font_line_size];

    for (std::size_t i = 0; i < g_font_line_size; ++i)
        g_framebuffer[limit + i] = 0;
}

void newline()
{
    g_current_width = 0;

    if (g_current_height + Font::Glyph::HEIGHT > g_last_font_column)
        scroll();
    else
        g_current_height += Font::Glyph::HEIGHT;
}

void put_glyph(Font::Glyph glyph)
{
    for (unsigned int i = 0; i < Font::Glyph::HEIGHT; ++i)
    {
        unsigned int const height = g_current_height + i;

        for (unsigned int j = 0; j < Font::Glyph::WIDTH; ++j)
        {
            unsigned int const width = g_current_width + j;
            std::size_t const idx = height * g_pixels_per_scan_line + width;

            if (glyph.data[i] & (0x80 >> j))
                g_framebuffer[idx] =
                    g_color_array[to_underlying_type(g_current_fg_color)];
            else
                g_framebuffer[idx] =
                    g_color_array[to_underlying_type(g_current_bg_color)];
        }
    }
}

} // end anonymous namespace

Error Framebuffer::init(EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE const &gop_mode)
{
    g_framebuffer = reinterpret_cast<std::uint32_t *>(gop_mode.FrameBufferBase);
    g_framebuffer_size = gop_mode.FrameBufferSize;
    g_max_width = gop_mode.Info->HorizontalResolution;
    g_max_height = gop_mode.Info->VerticalResolution;
    g_pixels_per_scan_line = gop_mode.Info->PixelsPerScanLine;
    g_current_width = 0;
    g_current_height = 0;
    g_font_line_size = Font::Glyph::HEIGHT * g_pixels_per_scan_line;
    g_last_font_column = g_max_height - Font::Glyph::HEIGHT;

    switch (gop_mode.Info->PixelFormat)
    {
    case PixelRedGreenBlueReserved8BitPerColor:
        g_color_array[to_underlying_type(Color::BLACK)] = 0x00000000;
        g_color_array[to_underlying_type(Color::WHITE)] = 0x00ffffff;
        g_color_array[to_underlying_type(Color::RED)] = 0x000000ff;
        g_color_array[to_underlying_type(Color::LIME)] = 0x0000ff00;
        g_color_array[to_underlying_type(Color::BLUE)] = 0x00ff0000;
        g_color_array[to_underlying_type(Color::YELLOW)] = 0x0000ffff;
        g_color_array[to_underlying_type(Color::CYAN)] = 0x00ffff00;
        g_color_array[to_underlying_type(Color::MAGENTA)] = 0x00ff00ff;
        g_color_array[to_underlying_type(Color::SILVER)] = 0x00c0c0c0;
        g_color_array[to_underlying_type(Color::GRAY)] = 0x00808080;
        g_color_array[to_underlying_type(Color::MAROON)] = 0x00000080;
        g_color_array[to_underlying_type(Color::OLIVE)] = 0x00008080;
        g_color_array[to_underlying_type(Color::GREEN)] = 0x00008000;
        g_color_array[to_underlying_type(Color::PURPLE)] = 0x00800080;
        g_color_array[to_underlying_type(Color::TEAL)] = 0x00808000;
        g_color_array[to_underlying_type(Color::NAVY)] = 0x00800000;
        break;
    case PixelBlueGreenRedReserved8BitPerColor:
        g_color_array[to_underlying_type(Color::BLACK)] = 0x00000000;
        g_color_array[to_underlying_type(Color::WHITE)] = 0x00ffffff;
        g_color_array[to_underlying_type(Color::RED)] = 0x00ff0000;
        g_color_array[to_underlying_type(Color::LIME)] = 0x0000ff00;
        g_color_array[to_underlying_type(Color::BLUE)] = 0x000000ff;
        g_color_array[to_underlying_type(Color::YELLOW)] = 0x00ffff00;
        g_color_array[to_underlying_type(Color::CYAN)] = 0x0000ffff;
        g_color_array[to_underlying_type(Color::MAGENTA)] = 0x00ff00ff;
        g_color_array[to_underlying_type(Color::SILVER)] = 0x00c0c0c0;
        g_color_array[to_underlying_type(Color::GRAY)] = 0x00808080;
        g_color_array[to_underlying_type(Color::MAROON)] = 0x00800000;
        g_color_array[to_underlying_type(Color::OLIVE)] = 0x00808000;
        g_color_array[to_underlying_type(Color::GREEN)] = 0x00008000;
        g_color_array[to_underlying_type(Color::PURPLE)] = 0x00800080;
        g_color_array[to_underlying_type(Color::TEAL)] = 0x00008080;
        g_color_array[to_underlying_type(Color::NAVY)] = 0x00000080;
        break;
    case PixelBitMask:
    case PixelBltOnly:
    case PixelFormatMax:
        return Error::INVALID;
    }

    g_current_bg_color = Color::BLACK;
    g_current_fg_color = Color::WHITE;

    return Error::SUCCESS;
}

void Framebuffer::put_char(char c)
{
    if (c == '\n')
    {
        newline();
        return;
    }

    if (g_current_width + Font::Glyph::HEIGHT > g_max_width)
        newline();

    put_glyph(Font::get_glyph(c));

    g_current_width += Font::Glyph::WIDTH;
}

void Framebuffer::put_string(StringRef x)
{
    for (char const c : x)
        put_char(c);
}

void Framebuffer::clear_screen()
{
    set_array(g_framebuffer,
              g_color_array[to_underlying_type(g_current_bg_color)],
              g_framebuffer_size);
    g_current_height = g_current_width = 0;
}

Error Framebuffer::print_func(StringRef s)
{
    put_string(s);
    return Error::SUCCESS;
}

void Framebuffer::set_foreground_color(Color color)
{
    g_current_fg_color = color;
}

void Framebuffer::set_background_color(Color color)
{
    g_current_bg_color = color;
}
