/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_LIBLCD_LCDDISPLAY_H
#define INCLUDED_LIBLCD_LCDDISPLAY_H

#include <string>

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

    LCDAPI void write(const char *format, ...);
    LCDAPI bool scroll(const char *format, ...);
    LCDAPI void interrupt();

    LCDAPI unsigned int getWidth();
    LCDAPI unsigned int getHeight();

    // Special codes
    LCDAPI void displayOn();
    LCDAPI void displayOff();
    LCDAPI void cursorOn();
    LCDAPI void cursorOff();
    LCDAPI void blinkOn();
    LCDAPI void blinkOff();
    LCDAPI void backlightOn();
    LCDAPI void backlightOff();
    LCDAPI void flashBacklight();
    LCDAPI void clear();
    LCDAPI void back();
    LCDAPI void smallFont();
    LCDAPI void largeFont();
    LCDAPI void oneLine();
    LCDAPI void twoLines();
    LCDAPI void gotoLineBegin();
    LCDAPI void newLine();
    LCDAPI void shiftCursorLeft();
    LCDAPI void shiftCursorRight();
    LCDAPI void shiftDisplayLeft();
    LCDAPI void shiftDisplayRight();
    LCDAPI void killEOL();
    LCDAPI void reinit();
    LCDAPI void gotoXY(int x, int y);
    LCDAPI void gotoLastLine();

private:
    void _interrupt();
    void _write(const std::string &str);
    int m_fd;
    unsigned int m_width;
    unsigned int m_height;
    bool m_interrupt;
};

} // namespace liblcd

#endif // INCLUDED_LIBLCD_LCDDISPLAY_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
