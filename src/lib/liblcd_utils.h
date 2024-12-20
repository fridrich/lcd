/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBLCD_UTILS_H
#define INCLUDED_LIBLCD_UTILS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>
#include <string>
#include <cstdarg>

#if defined(HAVE_FUNC_ATTRIBUTE_FORMAT)
#  define LCD_ATTRIBUTE_PRINTF(fmt, arg) __attribute__((__format__(__printf__, fmt, arg)))
#else
#  define LCD_ATTRIBUTE_PRINTF(fmt, arg)
#endif

// do nothing with debug messages in a release compile
#ifdef DEBUG
namespace liblcd
{
void debugPrint(const char *format, ...) LCD_ATTRIBUTE_PRINTF(1, 2);
}

#define LCD_DEBUG_MSG(M) liblcd::debugPrint M
#define LCD_DEBUG(M) M
#else
#define LCD_DEBUG_MSG(M)
#define LCD_DEBUG(M)
#endif

#define LCD_NUM_ELEMENTS(array) (sizeof(array) / sizeof(array[0]))

namespace liblcd
{

bool isBigEndian();

unsigned readU32(FILE *input);

unsigned readU32Node(const char *nodeName);

void sprintf(std::string &result, const char *format, ...);

void _sprintf(std::string &result, const char *format, std::va_list *args);

void utf8_to_hd44780(std::string &result);

} // namespace liblcd

#endif // INCLUDED_LIBLCD_UTILS_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
