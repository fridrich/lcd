/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <liblcd/liblcd.h>

#include "liblcd_utils.h"

namespace
{

static bool isBigEndian()
{
    static unsigned i = 1;
    return (*(unsigned char *)&i) == 1;
}

unsigned readU32(FILE *input)
{
    unsigned char p[sizeof(uint32_t)];
    size_t numBytesRead = fread(p, 1, sizeof(uint32_t), input);
    if (numBytesRead != sizeof(uint32_t))
    {
        perror("Unable to read enough data");
        return 0;
    }
    else
    {
        if (isBigEndian())
            return (uint32_t)p[3]|((uint32_t)p[2]<<8)|((uint32_t)p[1]<<16)|((uint32_t)p[0]<<24);
        return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);
    }

}

static unsigned readU32Node(const char *nodeName)
{
    FILE *f = fopen(nodeName, "r");
    if (f == NULL)
    {
        perror("Error opening node");
        return 0;
    }
    unsigned value = readU32(f);
    fclose(f);
    return value;
}

} // anonymous namespace

liblcd::LCDDisplay::LCDDisplay() : m_fd(-1), m_width(0), m_height(0)
{
    m_fd = open("/dev/lcd", O_WRONLY);
    if (m_fd == -1)
    {
        perror("Error opening file");
    }
    else
    {
        backlightOn();
    }
    m_width = readU32Node("/sys/devices/platform/auxdisplay/of_node/display-width-chars");
    m_height= readU32Node("/sys/devices/platform/auxdisplay/of_node/display-height-chars");
    LCD_DEBUG_MSG(("Display width %u, height %u\n", m_width, m_height));
}

liblcd::LCDDisplay::~LCDDisplay()
{
    if (m_fd != -1)
    {
        close(m_fd);
    }
}

void liblcd::LCDDisplay::write(const char *buffer)
{
    if (m_fd != -1)
    {
        ::write(m_fd, buffer, strlen(buffer));
    }
}

void liblcd::LCDDisplay::scroll(const char *buffer)
{
    write(buffer);
    usleep(0.5 * 1000000.0);
    for (unsigned i = 0; i < strlen(buffer)+1; i++)
    {
        write(buffer+i);
        killEOL(); // kill the end of the line (means pad it by spaces)
        gotoLineBegin(); // return cursor at the beginning of the current line
        usleep(0.4 * 1000000.0);
    }
    write(buffer);
}

unsigned int liblcd::LCDDisplay::getWidth()
{
    return m_width;
}

unsigned int liblcd::LCDDisplay::getHeight()
{
    return m_height;
}

void liblcd::LCDDisplay::displayOn()
{
    write("\x1b[LD");
}

void liblcd::LCDDisplay::displayOff()
{
    write("\x1b[Ld");
}

void liblcd::LCDDisplay::cursorOn()
{
    write("\x1b[LC");
}

void liblcd::LCDDisplay::cursorOff()
{
    write("\x1b[Lc");
}

void liblcd::LCDDisplay::blinkOn()
{
    write("\x1b[LB");
}

void liblcd::LCDDisplay::blinkOff()
{
    write("\x1b[Lb");
}

void liblcd::LCDDisplay::backlightOn()
{
    write("\x1b[L+");
}

void liblcd::LCDDisplay::backlightOff()
{
    write("\x1b[L-");
}

void liblcd::LCDDisplay::flashBacklight()
{
    write("\x1b[L*");
}

void liblcd::LCDDisplay::clear()
{
    write("\f");
}

void liblcd::LCDDisplay::back()
{
    write("\b");
}

void liblcd::LCDDisplay::smallFont()
{
    write("\x1b[Lf");
}

void liblcd::LCDDisplay::largeFont()
{
    write("\x1b[LF");
}

void liblcd::LCDDisplay::oneLine()
{
    write("\x1b[Ln");
}

void liblcd::LCDDisplay::twoLines()
{
    write("\x1b[LN");
}

void liblcd::LCDDisplay::gotoLineBegin()
{
    write("\r");
}

void liblcd::LCDDisplay::newLine()
{
    write("\n");
}

void liblcd::LCDDisplay::shiftCursorLeft()
{
    write("\x1b[Ll");
}

void liblcd::LCDDisplay::shiftCursorRight()
{
    write("\x1b[Lr");
}

void liblcd::LCDDisplay::shiftDisplayLeft()
{
    write("\x1b[LL");
}

void liblcd::LCDDisplay::shiftDisplayRight()
{
    write("\x1b[LR");
}

void liblcd::LCDDisplay::killEOL()
{
    write("\x1b[Lk");
}

void liblcd::LCDDisplay::reinit()
{
    write("\x1b[LI");
}

void liblcd::LCDDisplay::gotoXY(int x, int y)
{
    char xString[100];
    char yString[100];
    std::string buffer;
    buffer.append("x1b[L");
    if (x >= 0)
    {
        snprintf(&xString[0], 100, "%d", x);
        buffer.append("x");
        buffer.append(&xString[0]);
        LCD_DEBUG_MSG(("X value %d, string %s\n", x, &xString[0]));
    }
    if (y >= 0)
    {
        snprintf(&yString[0], 100, "%d", y);
        buffer.append("y");
        buffer.append(&yString[0]);
        LCD_DEBUG_MSG(("Y value %d, string %s\n", y, &yString[0]));
    }
    buffer.append(";");
    LCD_DEBUG_MSG(("%s\n", buffer.c_str()));
    write(buffer.c_str());
}

void liblcd::LCDDisplay::gotoLastLine()
{
    gotoXY(0, m_height-1);
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
