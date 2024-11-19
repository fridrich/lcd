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
    return (*(unsigned char *)&i) != 1;
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
        write("\x1b[L+");
    }
    m_width = readU32Node("/sys/devices/platform/auxdisplay/of_node/display-width-chars");
    m_height= readU32Node("/sys/devices/platform/auxdisplay/of_node/display-width-chars");
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
        write("\x1b[Lk"); // kill the end of the line (means pad it by spaces)
        write("\r"); // return cursor at the beginning of the current line
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

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
