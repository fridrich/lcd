/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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

} // namespace liblcd

#endif // INCLUDED_LIBLCD_UTILS_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
