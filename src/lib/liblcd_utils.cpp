/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "liblcd_utils.h"

#ifdef DEBUG
#include <cstdarg>
#include <cstdio>
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

}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
