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

liblcd::LCDDisplay::LCDDisplay() : fd(-1)
{
    fd = open("/dev/lcd", O_WRONLY);
    if (fd == -1)
    {
        perror("Error opening file");
    }
    else
    {
        write("\x1b[L+");
    }
}

liblcd::LCDDisplay::~LCDDisplay()
{
    if (fd != -1)
    {
        close(fd);
    }
}

void liblcd::LCDDisplay::write(const char *buffer)
{
    if (fd != -1)
    {
        ::write(fd, buffer, strlen(buffer));
    }
}

void liblcd::LCDDisplay::scroll(const char *buffer)
{
    write(buffer);
    usleep(0.5 * 1000000.0);
    for (unsigned i = 0; i < strlen(buffer)+1; i++)
    {
        write(buffer+i);
        write("\x1b[Lk");
        write("\r");
        usleep(0.4 * 1000000.0);
    }
    write(buffer);
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
