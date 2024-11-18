/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBLCD_LCDDISPLAY_H
#define INCLUDED_LIBLCD_LCDDISPLAY_H

#ifdef LIBLCD_VISIBILITY
#define LCDAPI __attribute__((visibility("default")))
#else
#define LCDAPI
#endif

namespace liblcd
{

class LCDDisplay
{
public:
    LCDAPI LCDDisplay();
    LCDAPI ~LCDDisplay();

    LCDAPI void write(const char *buffer);
    LCDAPI void scroll(const char *buffer);
private:
    int fd;
};

} // namespace liblcd

#endif // INCLUDED_LIBLCD_LCDDISPLAY_H

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */