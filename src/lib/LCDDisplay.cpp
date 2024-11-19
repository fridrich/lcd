/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include <liblcd/liblcd.h>

#include "liblcd_utils.h"

#define FIRST_BUF_SIZE 128
#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif

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

void sprintf(std::string &result, const char *format, ...)
{
    va_list args;

    int bufsize = FIRST_BUF_SIZE;
    char firstBuffer[FIRST_BUF_SIZE];
    std::unique_ptr<char[]> workBuffer;
    char *buf = firstBuffer;

    while (true)
    {
        va_start(args, format);
        int outsize = vsnprintf(buf, size_t(bufsize), format, args);
        va_end(args);

        if ((outsize == -1) || (outsize == bufsize) || (outsize == bufsize - 1))
            bufsize = bufsize * 2;
        else if (outsize > bufsize)
            bufsize = outsize + 2;
        else
            break;

        workBuffer.reset(new char[bufsize]);
        buf = workBuffer.get();
    }
    result.append(buf);
}

} // anonymous namespace

liblcd::LCDDisplay::LCDDisplay() : m_fd(-1), m_width(0), m_height(0)
{
    m_fd = open("/dev/lcd", O_WRONLY);
    if (m_fd == -1)
    {
        perror("Error opening file");
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

void liblcd::LCDDisplay::write(const char *format, ...)
{
    if (m_fd != -1)
    {
        va_list args;
        std::string result;
        va_start(args, format);
        sprintf(result, format, args);
        va_end(args);
        ::write(m_fd, result.c_str(), result.length());
    }
}

void liblcd::LCDDisplay::scroll(const char *format, ...)
{
    if (m_fd != -1)
    {
        va_list args;
        std::string result;
        va_start(args, format);
        sprintf(result, format, args);
        va_end(args);

        gotoLineBegin(); // return cursor at the beginning of the current line
        killEOL(); // clear the line
        ::write(m_fd, result.c_str(), result.length());
        usleep(0.5 * 1000000.0);
        if (m_width < result.length())
        {
            for (unsigned i = 0; i < result.length()+1; i++)
            {
                gotoLineBegin();
                ::write(m_fd, result.c_str()+i, result.length()-i);
                killEOL(); // kill the end of the line (means pad it by spaces)
                usleep(0.4 * 1000000.0);
            }
            gotoLineBegin();
            ::write(m_fd, result.c_str(), result.length());
        }
    }
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
    std::string buffer;
    buffer.append("\x1b[L");
    if (x >= 0)
        sprintf(buffer, "x%d", x);
    if (y >= 0)
        sprintf(buffer, "y%d", y);
    buffer.append(";");
    write(buffer.c_str());
}

void liblcd::LCDDisplay::gotoLastLine()
{
    gotoXY(0, m_height-1);
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
