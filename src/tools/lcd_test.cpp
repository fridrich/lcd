/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the liblcd project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <unistd.h>
#include <liblcd/liblcd.h>

int main()
{
    liblcd::LCDDisplay display = liblcd::LCDDisplay();

    display.clear();
    display.backlightOn();
    display.blinkOff();
    display.scroll("Display test");
    display.gotoLastLine();
    int i = 3;
    while (i--)
    {
        display.scroll("Hello, how are you? I hope that you are fine.");
        sleep(1);
    }
    display.backlightOff();
    display.flashBacklight();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
