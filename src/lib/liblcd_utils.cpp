/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "liblcd_utils.h"
#include <cstdarg>

#ifdef DEBUG
#include <cstdio>
#endif

#define FIRST_BUF_SIZE 128
#ifdef _MSC_VER
#define vsnprintf _vsnprintf
#endif

using std::string;

namespace liblcd
{

#ifdef DEBUG
void debugPrint(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);
}
#endif

bool isBigEndian()
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

unsigned readU32Node(const char *nodeName)
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

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
