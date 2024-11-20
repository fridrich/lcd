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
#include <unordered_map>

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

const std::unordered_map<uint64_t, std::string> characterMapping
{
    { 0xc2a1, "!" }, // ¡ INVERTED EXCLAMATION MARK
    { 0xc2a3, "\xed" }, // £ Pound SIGN
    { 0xc2a5, "\x5c" }, // ¥ YEN SIGN
    { 0xc2aa, "a" }, // ª FEMININE ORDINAL INDICATOR
    { 0xc2b0, "\xdf" }, // DEGREE SIGN
    { 0xc2b5, "\xe4" }, // MICRO SIGN
    { 0xc2b7, "\xa5" }, // MIDDLE DOT
    { 0xc2ba, "o" }, // º MASCULINE ORDINAL INDICATOR
    { 0xc2bf, "?" }, // ¿ INVERTED QUESTION MARK
    { 0xc380, "A" }, // À LATIN CAPITAL LETTER A WITH GRAVE
    { 0xc381, "A" }, // Á LATIN CAPITAL LETTER A WITH ACUTE
    { 0xc382, "A" }, // Â LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    { 0xc383, "A" }, // Ã LATIN CAPITAL LETTER A WITH TILDE
    { 0xc384, "A" }, // Ä LATIN CAPITAL LETTER A WITH DIAERESIS
    { 0xc385, "A" }, // Å LATIN CAPITAL LETTER A WITH RING ABOVE
    { 0xc386, "A" }, // Æ LATIN CAPITAL LETTER AE
    { 0xc387, "C" }, // Ç LATIN CAPITAL LETTER C WITH CEDILLA
    { 0xc388, "E" }, // È LATIN CAPITAL LETTER E WITH GRAVE
    { 0xc389, "E" }, // É LATIN CAPITAL LETTER E WITH ACUTE
    { 0xc38a, "E" }, // Ê LATIN CAPITAL LETTER E WITH CIRCUMFLEX
    { 0xc38b, "E" }, // Ë LATIN CAPITAL LETTER E WITH DIAERESIS
    { 0xc38c, "I" }, // Ì LATIN CAPITAL LETTER I WITH GRAVE
    { 0xc38d, "I" }, // Í LATIN CAPITAL LETTER I WITH ACUTE
    { 0xc38e, "I" }, // Î LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    { 0xc38f, "I" }, // Ï LATIN CAPITAL LETTER I WITH DIAERESIS
    { 0xc390, "D" }, // Ð LATIN CAPITAL LETTER ETH
    { 0xc391, "N" }, // Ñ LATIN CAPITAL LETTER N WITH TILDE
    { 0xc392, "O" }, // Ò LATIN CAPITAL LETTER O WITH GRAVE
    { 0xc393, "O" }, // Ó LATIN CAPITAL LETTER O WITH ACUTE
    { 0xc394, "O" }, // Ô LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    { 0xc395, "O" }, // Õ LATIN CAPITAL LETTER O WITH TILDE
    { 0xc396, "O" }, // Ö LATIN CAPITAL LETTER O WITH DIAERESIS
    { 0xc397, "*" }, // × MULTIPLICATION SIGN
    { 0xc398, "O" }, // Ø LATIN CAPITAL LETTER O WITH STROKE
    { 0xc399, "U" }, // Ù LATIN CAPITAL LETTER U WITH GRAVE
    { 0xc39a, "U" }, // Ú LATIN CAPITAL LETTER U WITH ACUTE
    { 0xc39b, "U" }, // Û LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    { 0xc39c, "U" }, // Ü LATIN CAPITAL LETTER U WITH DIAERESIS
    { 0xc39d, "Y" }, // Ý LATIN CAPITAL LETTER Y WITH ACUTE
    { 0xc39e, "p" }, // Þ LATIN CAPITAL LETTER THORN - somehow
    { 0xc39f, "\xe2" }, // ß LATIN SMALL LETTER SHARP S
    { 0xc3a0, "a" }, // à LATIN SMALL LETTER A WITH GRAVE
    { 0xc3a1, "a" }, // á LATIN SMALL LETTER A WITH ACUTE
    { 0xc3a2, "a" }, // â LATIN SMALL LETTER A WITH CIRCUMFLEX
    { 0xc3a3, "a" }, // ã LATIN SMALL LETTER A WITH TILDE
    { 0xc3a4, "\xe1" }, // ä LATIN SMALL LETTER A WITH DIAERESIS
    { 0xc3a5, "a" }, // å LATIN SMALL LETTER A WITH RING ABOVE
    { 0xc3a6, "a" }, // æ LATIN SMALL LETTER AE
    { 0xc3a7, "c" }, // ç LATIN SMALL LETTER C WITH CEDILLA
    { 0xc3a8, "e" }, // è LATIN SMALL LETTER E WITH GRAVE
    { 0xc3a9, "e" }, // é LATIN SMALL LETTER E WITH ACUTE
    { 0xc3aa, "e" }, // ê LATIN SMALL LETTER E WITH CIRCUMFLEX
    { 0xc3ab, "e" }, // ë LATIN SMALL LETTER E WITH DIAERESIS
    { 0xc3ac, "i" }, // ì LATIN SMALL LETTER I WITH GRAVE
    { 0xc3ad, "i" }, // í LATIN SMALL LETTER I WITH ACUTE
    { 0xc3ae, "i" }, // î LATIN SMALL LETTER I WITH CIRCUMFLEX
    { 0xc3af, "i" }, // ï LATIN SMALL LETTER I WITH DIAERESIS
    { 0xc3b0, "e" }, // ð LATIN SMALL LETTER ETH
    { 0xc3b1, "\xee" }, // ñ LATIN SMALL LETTER N WITH TILDE
    { 0xc3b2, "o" }, // ò LATIN SMALL LETTER O WITH GRAVE
    { 0xc3b3, "o" }, // ó LATIN SMALL LETTER O WITH ACUTE
    { 0xc3b4, "o" }, // ô LATIN SMALL LETTER O WITH CIRCUMFLEX
    { 0xc3b5, "o" }, // õ LATIN SMALL LETTER O WITH TILDE
    { 0xc3b6, "\xef" }, // ö LATIN SMALL LETTER O WITH DIAERESIS
    { 0xc3b7, "\xfd" }, // ÷ DIVISION SIGN - somehow
    { 0xc3b8, "o" }, // ø LATIN SMALL LETTER O WITH STROKE
    { 0xc3b9, "u" }, // ù LATIN SMALL LETTER U WITH GRAVE
    { 0xc3ba, "u" }, // ú LATIN SMALL LETTER U WITH ACUTE
    { 0xc3bb, "u" }, // û LATIN SMALL LETTER U WITH CIRCUMFLEX
    { 0xc3bc, "\xf5" }, // ü LATIN SMALL LETTER U WITH DIAERESIS
    { 0xc3bd, "y" }, // ý LATIN SMALL LETTER Y WITH ACUTE
    { 0xc3be, "p" }, // þ LATIN SMALL LETTER THORN - somehow
    { 0xc3bf, "y" }, // ÿ LATIN SMALL LETTER Y WITH DIAERESIS
    { 0xc480, "A" }, // Ā LATIN CAPITAL LETTER A WITH MACRON
    { 0xc481, "a" }, // ā LATIN SMALL LETTER A WITH MACRON
    { 0xc482, "A" }, // Ă LATIN CAPITAL LETTER A WITH BREVE
    { 0xc483, "a" }, // ă LATIN SMALL LETTER A WITH BREVE
    { 0xc484, "A" }, // Ą LATIN CAPITAL LETTER A WITH OGONEK
    { 0xc485, "a" }, // ą LATIN SMALL LETTER A WITH OGONEK
    { 0xc486, "C" }, // Ć LATIN CAPITAL LETTER C WITH ACUTE
    { 0xc487, "c" }, // ć LATIN SMALL LETTER C WITH ACUTE
    { 0xc488, "C" }, // Ĉ LATIN CAPITAL LETTER C WITH CIRCUMFLEX
    { 0xc489, "c" }, // ĉ LATIN SMALL LETTER C WITH CIRCUMFLEX
    { 0xc48a, "C" }, //   LATIN CAPITAL LETTER C WITH DOT ABOVE
    { 0xc48b, "c" }, // ċ LATIN SMALL LETTER C WITH DOT ABOVE
    { 0xc48c, "C" }, // Č LATIN CAPITAL LETTER C WITH CARON
    { 0xc48d, "c" }, // č LATIN SMALL LETTER C WITH CARON
    { 0xc48e, "D" }, // Ď LATIN CAPITAL LETTER D WITH CARON
    { 0xc48f, "d" }, // ď LATIN SMALL LETTER D WITH CARON
    { 0xc490, "D" }, // Đ LATIN CAPITAL LETTER D WITH STROKE
    { 0xc491, "d" }, // đ LATIN SMALL LETTER D WITH STROKE
    { 0xc492, "E" }, // Ē LATIN CAPITAL LETTER E WITH MACRON
    { 0xc493, "e" }, // ē LATIN SMALL LETTER E WITH MACRON
    { 0xc494, "E" }, // Ĕ LATIN CAPITAL LETTER E WITH BREVE
    { 0xc495, "e" }, // ĕ LATIN SMALL LETTER E WITH BREVE
    { 0xc496, "E" }, // Ė LATIN CAPITAL LETTER E WITH DOT ABOVE
    { 0xc497, "e" }, // ė LATIN SMALL LETTER E WITH DOT ABOVE
    { 0xc498, "E" }, // Ę LATIN CAPITAL LETTER E WITH OGONEK
    { 0xc499, "e" }, // ę LATIN SMALL LETTER E WITH OGONEK
    { 0xc49a, "E" }, // Ě LATIN CAPITAL LETTER E WITH CARON
    { 0xc49b, "e" }, // ě LATIN SMALL LETTER E WITH CARON
    { 0xc49c, "G" }, // Ĝ LATIN CAPITAL LETTER G WITH CIRCUMFLEX
    { 0xc49d, "g" }, // ĝ LATIN SMALL LETTER G WITH CIRCUMFLEX
    { 0xc49e, "G" }, // Ğ LATIN CAPITAL LETTER G WITH BREVE
    { 0xc49f, "g" }, // ğ LATIN SMALL LETTER G WITH BREVE
    { 0xc4a0, "G" }, // Ġ LATIN CAPITAL LETTER G WITH DOT ABOVE
    { 0xc4a1, "g" }, // ġ LATIN SMALL LETTER G WITH DOT ABOVE
    { 0xc4a2, "G" }, // Ģ LATIN CAPITAL LETTER G WITH CEDILLA
    { 0xc4a3, "g" }, // ģ LATIN SMALL LETTER G WITH CEDILLA
    { 0xc4a4, "H" }, // Ĥ LATIN CAPITAL LETTER H WITH CIRCUMFLEX
    { 0xc4a5, "h" }, // ĥ LATIN SMALL LETTER H WITH CIRCUMFLEX
    { 0xc4a6, "H" }, // Ħ LATIN CAPITAL LETTER H WITH STROKE
    { 0xc4a7, "h" }, // ħ LATIN SMALL LETTER H WITH STROKE
    { 0xc4a8, "I" }, // Ĩ LATIN CAPITAL LETTER I WITH TILDE
    { 0xc4a9, "i" }, // ĩ LATIN SMALL LETTER I WITH TILDE
    { 0xc4aa, "I" }, // Ī LATIN CAPITAL LETTER I WITH MACRON
    { 0xc4ab, "i" }, // ī LATIN SMALL LETTER I WITH MACRON
    { 0xc4ac, "I" }, // Ĭ LATIN CAPITAL LETTER I WITH BREVE
    { 0xc4ad, "i" }, // ĭ LATIN SMALL LETTER I WITH BREVE
    { 0xc4ae, "I" }, // Į LATIN CAPITAL LETTER I WITH OGONEK
    { 0xc4af, "i" }, // į LATIN SMALL LETTER I WITH OGONEK
    { 0xc4b0, "I" }, // İ LATIN CAPITAL LETTER I WITH DOT ABOVE
    { 0xc4b1, "i" }, // ı LATIN SMALL LETTER DOTLESS I
    { 0xc4b2, "I" }, // Ĳ LATIN CAPITAL LIGATURE IJ
    { 0xc4b3, "i" }, // ĳ LATIN SMALL LIGATURE IJ
    { 0xc4b4, "J" }, // Ĵ LATIN CAPITAL LETTER J WITH CIRCUMFLEX
    { 0xc4b5, "j" }, // ĵ LATIN SMALL LETTER J WITH CIRCUMFLEX
    { 0xc4b6, "K" }, // Ķ LATIN CAPITAL LETTER K WITH CEDILLA
    { 0xc4b7, "k" }, // ķ LATIN SMALL LETTER K WITH CEDILLA
    { 0xc4b8, "k" }, // ĸ LATIN SMALL LETTER KRA
    { 0xc4b9, "L" }, // Ĺ LATIN CAPITAL LETTER L WITH ACUTE
    { 0xc4ba, "l" }, // ĺ LATIN SMALL LETTER L WITH ACUTE
    { 0xc4bb, "L" }, // Ļ LATIN CAPITAL LETTER L WITH CEDILLA
    { 0xc4bc, "l" }, // ļ LATIN SMALL LETTER L WITH CEDILLA
    { 0xc4bd, "L" }, // Ľ LATIN CAPITAL LETTER L WITH CARON
    { 0xc4be, "l" }, // ľ LATIN SMALL LETTER L WITH CARON
    { 0xc4bf, "L" }, // Ŀ LATIN CAPITAL LETTER L WITH MIDDLE DOT
    { 0xc580, "l" }, // ŀ LATIN SMALL LETTER L WITH MIDDLE DOT
    { 0xc581, "L" }, // Ł LATIN CAPITAL LETTER L WITH STROKE
    { 0xc582, "l" }, // ł LATIN SMALL LETTER L WITH STROKE
    { 0xc583, "N" }, // Ń LATIN CAPITAL LETTER N WITH ACUTE
    { 0xc584, "n" }, // ń LATIN SMALL LETTER N WITH ACUTE
    { 0xc585, "N" }, // Ņ LATIN CAPITAL LETTER N WITH CEDILLA
    { 0xc586, "n" }, // ņ LATIN SMALL LETTER N WITH CEDILLA
    { 0xc587, "N" }, // Ň LATIN CAPITAL LETTER N WITH CARON
    { 0xc588, "n" }, // ň LATIN SMALL LETTER N WITH CARON
    { 0xc589, "n" }, // ŉ LATIN SMALL LETTER N PRECEDED BY APOSTROPHE
    { 0xc58a, "N" }, // Ŋ LATIN CAPITAL LETTER ENG
    { 0xc58b, "n" }, // ŋ LATIN SMALL LETTER ENG
    { 0xc58c, "O" }, // Ō LATIN CAPITAL LETTER O WITH MACRON
    { 0xc58d, "o" }, // ō LATIN SMALL LETTER O WITH MACRON
    { 0xc58e, "O" }, // Ŏ LATIN CAPITAL LETTER O WITH BREVE
    { 0xc58f, "o" }, // ŏ LATIN SMALL LETTER O WITH BREVE
    { 0xc590, "O" }, // Ő LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
    { 0xc591, "o" }, // ő LATIN SMALL LETTER O WITH DOUBLE ACUTE
    { 0xc592, "O" }, // Œ LATIN CAPITAL LIGATURE OE
    { 0xc593, "o" }, // œ LATIN SMALL LIGATURE OE
    { 0xc594, "R" }, // Ŕ LATIN CAPITAL LETTER R WITH ACUTE
    { 0xc595, "r" }, // ŕ LATIN SMALL LETTER R WITH ACUTE
    { 0xc596, "R" }, // Ŗ LATIN CAPITAL LETTER R WITH CEDILLA
    { 0xc597, "r" }, // ŗ LATIN SMALL LETTER R WITH CEDILLA
    { 0xc598, "R" }, // Ř LATIN CAPITAL LETTER R WITH CARON
    { 0xc599, "r" }, // ř LATIN SMALL LETTER R WITH CARON
    { 0xc59a, "S" }, // Ś LATIN CAPITAL LETTER S WITH ACUTE
    { 0xc59b, "s" }, // ś LATIN SMALL LETTER S WITH ACUTE
    { 0xc59c, "S" }, // Ŝ LATIN CAPITAL LETTER S WITH CIRCUMFLEX
    { 0xc59d, "s" }, // ŝ LATIN SMALL LETTER S WITH CIRCUMFLEX
    { 0xc59e, "S" }, // Ş LATIN CAPITAL LETTER S WITH CEDILLA
    { 0xc59f, "s" }, // ş LATIN SMALL LETTER S WITH CEDILLA
    { 0xc5a0, "S" }, // Š LATIN CAPITAL LETTER S WITH CARON
    { 0xc5a1, "s" }, // š LATIN SMALL LETTER S WITH CARON
    { 0xc5a2, "T" }, // Ţ LATIN CAPITAL LETTER T WITH CEDILLA
    { 0xc5a3, "t" }, // ţ LATIN SMALL LETTER T WITH CEDILLA
    { 0xc5a4, "T" }, // Ť LATIN CAPITAL LETTER T WITH CARON
    { 0xc5a5, "t" }, // ť LATIN SMALL LETTER T WITH CARON
    { 0xc5a6, "T" }, // Ŧ LATIN CAPITAL LETTER T WITH STROKE
    { 0xc5a7, "t" }, // ŧ LATIN SMALL LETTER T WITH STROKE
    { 0xc5a8, "U" }, // Ũ LATIN CAPITAL LETTER U WITH TILDE
    { 0xc5a9, "u" }, // ũ LATIN SMALL LETTER U WITH TILDE
    { 0xc5aa, "U" }, // Ū LATIN CAPITAL LETTER U WITH MACRON
    { 0xc5ab, "u" }, // ū LATIN SMALL LETTER U WITH MACRON
    { 0xc5ac, "U" }, // Ŭ LATIN CAPITAL LETTER U WITH BREVE
    { 0xc5ad, "u" }, // ŭ LATIN SMALL LETTER U WITH BREVE
    { 0xc5ae, "U" }, // Ů LATIN CAPITAL LETTER U WITH RING ABOVE
    { 0xc5af, "u" }, // ů LATIN SMALL LETTER U WITH RING ABOVE
    { 0xc5b0, "U" }, // Ű LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
    { 0xc5b1, "u" }, // ű LATIN SMALL LETTER U WITH DOUBLE ACUTE
    { 0xc5b2, "U" }, // Ų LATIN CAPITAL LETTER U WITH OGONEK
    { 0xc5b3, "u" }, // ų LATIN SMALL LETTER U WITH OGONEK
    { 0xc5b4, "W" }, // Ŵ LATIN CAPITAL LETTER W WITH CIRCUMFLEX
    { 0xc5b5, "w" }, // ŵ LATIN SMALL LETTER W WITH CIRCUMFLEX
    { 0xc5b6, "Y" }, // Ŷ LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
    { 0xc5b7, "y" }, // ŷ LATIN SMALL LETTER Y WITH CIRCUMFLEX
    { 0xc5b8, "Y" }, // Ÿ LATIN CAPITAL LETTER Y WITH DIAERESIS
    { 0xc5b9, "Z" }, // Ź LATIN CAPITAL LETTER Z WITH ACUTE
    { 0xc5ba, "z" }, // ź LATIN SMALL LETTER Z WITH ACUTE
    { 0xc5bb, "Z" }, // Ż LATIN CAPITAL LETTER Z WITH DOT ABOVE
    { 0xc5bc, "z" }, // ż LATIN SMALL LETTER Z WITH DOT ABOVE
    { 0xc5bd, "Z" }, // Ž LATIN CAPITAL LETTER Z WITH CARON
    { 0xc5be, "z" }, // ž LATIN SMALL LETTER Z WITH CARON
    { 0xc5bf, "s" }, // ſ LATIN SMALL LETTER LONG S
    { 0xc680, "b" }, // ƀ LATIN SMALL LETTER B WITH STROKE
    { 0xc681, "B" }, // Ɓ LATIN CAPITAL LETTER B WITH HOOK
    { 0xc682, "B" }, // Ƃ LATIN CAPITAL LETTER B WITH TOPBAR
    { 0xc683, "b" }, // ƃ LATIN SMALL LETTER B WITH TOPBAR
    { 0xc684, "B" }, // Ƅ LATIN CAPITAL LETTER TONE SIX - somehow
    { 0xc685, "b" }, // ƅ LATIN SMALL LETTER TONE SIX - somehow
    { 0xc686, "O" }, // Ɔ LATIN CAPITAL LETTER OPEN O
    { 0xc687, "C" }, // Ƈ LATIN CAPITAL LETTER C WITH HOOK
    { 0xc688, "c" }, // ƈ LATIN SMALL LETTER C WITH HOOK
    { 0xc689, "D" }, // Ɖ LATIN CAPITAL LETTER AFRICAN D
    { 0xc68a, "D" }, // Ɗ LATIN CAPITAL LETTER D WITH HOOK
    { 0xc68b, "D" }, // Ƌ LATIN CAPITAL LETTER D WITH TOPBAR
    { 0xc68c, "d" }, // ƌ LATIN SMALL LETTER D WITH TOPBAR
    { 0xc68e, "E" }, // Ǝ LATIN CAPITAL LETTER REVERSED E
    { 0xc690, "E" }, // Ɛ LATIN CAPITAL LETTER OPEN E
    { 0xc691, "F" }, // Ƒ LATIN CAPITAL LETTER F WITH HOOK
    { 0xc692, "f" }, // ƒ LATIN SMALL LETTER F WITH HOOK
    { 0xc693, "G" }, // Ɠ LATIN CAPITAL LETTER G WITH HOOK
    { 0xc697, "I" }, // Ɨ LATIN CAPITAL LETTER I WITH STROKE
    { 0xc698, "K" }, // Ƙ LATIN CAPITAL LETTER K WITH HOOK
    { 0xc699, "k" }, // ƙ LATIN SMALL LETTER K WITH HOOK
    { 0xc69a, "l" }, // ƚ LATIN SMALL LETTER L WITH BAR
    { 0xc69c, "M" }, // Ɯ LATIN CAPITAL LETTER TURNED M
    { 0xc69d, "N" }, // Ɲ LATIN CAPITAL LETTER N WITH LEFT HOOK
    { 0xc69e, "n" }, // ƞ LATIN SMALL LETTER N WITH LONG RIGHT LEG
    { 0xc69f, "\xf2" }, // Ɵ LATIN CAPITAL LETTER O WITH MIDDLE TILDE
    { 0xc6a0, "o" }, // ơ LATIN SMALL LETTER O WITH HORN
    { 0xc6a4, "P" }, // Ƥ LATIN CAPITAL LETTER P WITH HOOK
    { 0xc6a5, "p" }, // ƥ LATIN SMALL LETTER P WITH HOOK
    { 0xc6ab, "t" }, // ƫ LATIN SMALL LETTER T WITH PALATAL HOOK
    { 0xc6ac, "T" }, // Ƭ LATIN CAPITAL LETTER T WITH HOOK
    { 0xc6ad, "t" }, // ƭ LATIN SMALL LETTER T WITH HOOK
    { 0xc6ae, "T" }, // Ʈ LATIN CAPITAL LETTER T WITH RETROFLEX HOOK
    { 0xc6af, "U" }, // Ư LATIN CAPITAL LETTER U WITH HORN
    { 0xc6b0, "u" }, // ư LATIN SMALL LETTER U WITH HORN
    { 0xc6b2, "V" }, // Ʋ LATIN CAPITAL LETTER V WITH HOOK
    { 0xc6b3, "Y" }, // Ƴ LATIN CAPITAL LETTER Y WITH HOOK
    { 0xc6b4, "y" }, // ƴ LATIN SMALL LETTER Y WITH HOOK
    { 0xc6b5, "Z" }, // Ƶ LATIN CAPITAL LETTER Z WITH STROKE
    { 0xc6b6, "z" }, // ƶ LATIN SMALL LETTER Z WITH STROKE
    { 0xc784, "D" }, // Ǆ LATIN CAPITAL LETTER DZ WITH CARON
    { 0xc785, "D" }, // ǅ LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
    { 0xc786, "d" }, // ǆ LATIN SMALL LETTER DZ WITH CARON
    { 0xc787, "L" }, // Ǉ LATIN CAPITAL LETTER LJ
    { 0xc788, "L" }, // ǈ LATIN CAPITAL LETTER L WITH SMALL LETTER J
    { 0xc789, "l" }, // ǉ LATIN SMALL LETTER LJ
    { 0xc78a, "N" }, // Ǌ LATIN CAPITAL LETTER NJ
    { 0xc78b, "N" }, // ǋ LATIN CAPITAL LETTER N WITH SMALL LETTER J
    { 0xc78c, "n" }, // ǌ LATIN SMALL LETTER NJ
    { 0xc78d, "A" }, // Ǎ LATIN CAPITAL LETTER A WITH CARON
    { 0xc78e, "a" }, // ǎ LATIN SMALL LETTER A WITH CARON
    { 0xc78f, "I" }, // Ǐ LATIN CAPITAL LETTER I WITH CARON
    { 0xc790, "i" }, // ǐ LATIN SMALL LETTER I WITH CARON
    { 0xc791, "O" }, // Ǒ LATIN CAPITAL LETTER O WITH CARON
    { 0xc792, "o" }, // ǒ LATIN SMALL LETTER O WITH CARON
    { 0xc793, "U" }, // Ǔ LATIN CAPITAL LETTER U WITH CARON
    { 0xc794, "u" }, // ǔ LATIN SMALL LETTER U WITH CARON
    { 0xc795, "U" }, // Ǖ LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON
    { 0xc796, "u" }, // ǖ LATIN SMALL LETTER U WITH DIAERESIS AND MACRON
    { 0xc797, "U" }, // Ǘ LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE
    { 0xc798, "u" }, // ǘ LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
    { 0xc799, "U" }, // Ǚ LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
    { 0xc79a, "u" }, // ǚ LATIN SMALL LETTER U WITH DIAERESIS AND CARON
    { 0xc79b, "U" }, // Ǜ LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE
    { 0xc79c, "u" }, // ǜ LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
    { 0xc79d, "e" }, // ǝ LATIN SMALL LETTER TURNED E
    { 0xc79e, "A" }, // Ǟ LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
    { 0xc79f, "a" }, // ǟ LATIN SMALL LETTER A WITH DIAERESIS AND MACRON
    { 0xc7a0, "A" }, // Ǡ LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON
    { 0xc7a1, "a" }, // ǡ LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON
    { 0xc7a2, "A" }, // Ǣ LATIN CAPITAL LETTER AE WITH MACRON
    { 0xc7a3, "a" }, // ǣ LATIN SMALL LETTER AE WITH MACRON
    { 0xc7a4, "G" }, // Ǥ LATIN CAPITAL LETTER G WITH STROKE
    { 0xc7a5, "g" }, // ǥ LATIN SMALL LETTER G WITH STROKE
    { 0xc7a6, "G" }, // Ǧ LATIN CAPITAL LETTER G WITH CARON
    { 0xc7a7, "g" }, // ǧ LATIN SMALL LETTER G WITH CARON
    { 0xc7a8, "K" }, // Ǩ LATIN CAPITAL LETTER K WITH CARON
    { 0xc7a9, "k" }, // ǩ LATIN SMALL LETTER K WITH CARON
    { 0xc7aa, "O" }, // Ǫ LATIN CAPITAL LETTER O WITH OGONEK
    { 0xc7ab, "o" }, // ǫ LATIN SMALL LETTER O WITH OGONEK
    { 0xc7ac, "O" }, // Ǭ LATIN CAPITAL LETTER O WITH OGONEK AND MACRON
    { 0xc7ad, "o" }, // ǭ LATIN SMALL LETTER O WITH OGONEK AND MACRON
    { 0xc7b0, "j" }, // ǰ LATIN SMALL LETTER J WITH CARON
    { 0xc7b1, "DZ" }, // Ǳ LATIN CAPITAL LETTER DZ
    { 0xc7b2, "Dz" }, // ǲ LATIN CAPITAL LETTER D WITH SMALL LETTER Z
    { 0xc7b3, "dz" }, // ǳ LATIN SMALL LETTER DZ
    { 0xc7b4, "G" }, // Ǵ LATIN CAPITAL LETTER G WITH ACUTE
    { 0xc7b5, "g" }, // ǵ LATIN SMALL LETTER G WITH ACUTE
    { 0xc7b8, "N" }, // Ǹ LATIN CAPITAL LETTER N WITH GRAVE
    { 0xc7b9, "n" }, // ǹ LATIN SMALL LETTER N WITH GRAVE
    { 0xc7ba, "A" }, // Ǻ LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE
    { 0xc7bb, "a" }, // ǻ LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
    { 0xc7bc, "A" }, // Ǽ LATIN CAPITAL LETTER AE WITH ACUTE
    { 0xc7bd, "a" }, // ǽ LATIN SMALL LETTER AE WITH ACUTE
    { 0xc7be, "O" }, // Ǿ LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
    { 0xc7bf, "o" }, // ǿ LATIN SMALL LETTER O WITH STROKE AND ACUTE
    { 0xc880, "A" }, // Ȁ LATIN CAPITAL LETTER A WITH DOUBLE GRAVE
    { 0xc881, "a" }, // ȁ LATIN SMALL LETTER A WITH DOUBLE GRAVE
    { 0xc882, "A" }, // Ȃ LATIN CAPITAL LETTER A WITH INVERTED BREVE
    { 0xc883, "a" }, // ȃ LATIN SMALL LETTER A WITH INVERTED BREVE
    { 0xc884, "E" }, // Ȅ LATIN CAPITAL LETTER E WITH DOUBLE GRAVE
    { 0xc885, "e" }, // ȅ LATIN SMALL LETTER E WITH DOUBLE GRAVE
    { 0xc886, "E" }, // Ȇ LATIN CAPITAL LETTER E WITH INVERTED BREVE
    { 0xc887, "e" }, // ȇ LATIN SMALL LETTER E WITH INVERTED BREVE
    { 0xc888, "I" }, // Ȉ LATIN CAPITAL LETTER I WITH DOUBLE GRAVE
    { 0xc889, "i" }, // ȉ LATIN SMALL LETTER I WITH DOUBLE GRAVE
    { 0xc88a, "I" }, //   LATIN CAPITAL LETTER I WITH INVERTED BREVE
    { 0xc88b, "i" }, // ȋ LATIN SMALL LETTER I WITH INVERTED BREVE
    { 0xc88c, "O" }, // Ȍ LATIN CAPITAL LETTER O WITH DOUBLE GRAVE
    { 0xc88d, "o" }, // ȍ LATIN SMALL LETTER O WITH DOUBLE GRAVE
    { 0xc88e, "O" }, // Ȏ LATIN CAPITAL LETTER O WITH INVERTED BREVE
    { 0xc88f, "o" }, // ȏ LATIN SMALL LETTER O WITH INVERTED BREVE
    { 0xc890, "R" }, // Ȑ LATIN CAPITAL LETTER R WITH DOUBLE GRAVE
    { 0xc891, "r" }, // ȑ LATIN SMALL LETTER R WITH DOUBLE GRAVE
    { 0xc892, "R" }, // Ȓ LATIN CAPITAL LETTER R WITH INVERTED BREVE
    { 0xc893, "r" }, // ȓ LATIN SMALL LETTER R WITH INVERTED BREVE
    { 0xc894, "U" }, // Ȕ LATIN CAPITAL LETTER U WITH DOUBLE GRAVE
    { 0xc895, "u" }, // ȕ LATIN SMALL LETTER U WITH DOUBLE GRAVE
    { 0xc896, "U" }, // Ȗ LATIN CAPITAL LETTER U WITH INVERTED BREVE
    { 0xc897, "u" }, // ȗ LATIN SMALL LETTER U WITH INVERTED BREVE
    { 0xc898, "S" }, // Ș LATIN CAPITAL LETTER S WITH COMMA BELOW
    { 0xc899, "s" }, // ș LATIN SMALL LETTER S WITH COMMA BELOW
    { 0xc89a, "T" }, // Ț LATIN CAPITAL LETTER T WITH COMMA BELOW
    { 0xc89b, "t" }, // ț LATIN SMALL LETTER T WITH COMMA BELOW
    { 0xc89e, "H" }, // Ȟ LATIN CAPITAL LETTER H WITH CARON
    { 0xc89f, "h" }, // ȟ LATIN SMALL LETTER H WITH CARON
    { 0xc8a0, "N" }, // Ƞ LATIN CAPITAL LETTER N WITH LONG RIGHT LEG
    { 0xc8a1, "d" }, // ȡ LATIN SMALL LETTER D WITH CURL
    { 0xc8a2, "O" }, // Ȣ LATIN CAPITAL LETTER OU
    { 0xc8a3, "o" }, // ȣ LATIN SMALL LETTER OU
    { 0xc8a4, "Z" }, // Ȥ LATIN CAPITAL LETTER Z WITH HOOK
    { 0xc8a5, "z" }, // ȥ LATIN SMALL LETTER Z WITH HOOK
    { 0xc8a6, "A" }, // Ȧ LATIN CAPITAL LETTER A WITH DOT ABOVE
    { 0xc8a7, "a" }, // ȧ LATIN SMALL LETTER A WITH DOT ABOVE
    { 0xc8a8, "E" }, // Ȩ LATIN CAPITAL LETTER E WITH CEDILLA
    { 0xc8a9, "e" }, // ȩ LATIN SMALL LETTER E WITH CEDILLA
    { 0xc8aa, "O" }, // Ȫ LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON
    { 0xc8ab, "o" }, // ȫ LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
    { 0xc8ac, "O" }, // Ȭ LATIN CAPITAL LETTER O WITH TILDE AND MACRON
    { 0xc8ad, "o" }, // ȭ LATIN SMALL LETTER O WITH TILDE AND MACRON
    { 0xc8ae, "O" }, // Ȯ LATIN CAPITAL LETTER O WITH DOT ABOVE
    { 0xc8af, "o" }, // ȯ LATIN SMALL LETTER O WITH DOT ABOVE
    { 0xc8b0, "O" }, // Ȱ LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON
    { 0xc8b1, "o" }, // ȱ LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
    { 0xc8b2, "y" }, // Ȳ LATIN CAPITAL LETTER Y WITH MACRON
    { 0xc8b3, "y" }, // ȳ LATIN SMALL LETTER Y WITH MACRON
    { 0xc8b4, "l" }, // ȴ LATIN SMALL LETTER L WITH CURL
    { 0xc8b5, "n" }, // ȵ LATIN SMALL LETTER N WITH CURL
    { 0xc8b6, "t" }, // ȶ LATIN SMALL LETTER T WITH CURL
    { 0xc8b7, "j" }, // ȷ LATIN SMALL LETTER DOTLESS J
    { 0xc8ba, "A" }, // Ⱥ LATIN CAPITAL LETTER A WITH STROKE
    { 0xc8bb, "C" }, // Ȼ LATIN CAPITAL LETTER C WITH STROKE
    { 0xc8bc, "c" }, // ȼ LATIN SMALL LETTER C WITH STROKE
    { 0xc8bd, "L" }, // Ƚ LATIN CAPITAL LETTER L WITH BAR
    { 0xc8be, "T" }, // Ⱦ LATIN CAPITAL LETTER T WITH DIAGONAL STROKE
    { 0xc8bf, "s" }, // ȿ LATIN SMALL LETTER S WITH SWASH TAIL
    { 0xc980, "z" }, // ɀ LATIN SMALL LETTER Z WITH SWASH TAIL
    { 0xc983, "B" }, // Ƀ LATIN CAPITAL LETTER B WITH STROKE
    { 0xc984, "U" }, // Ʉ LATIN CAPITAL LETTER U BAR
    { 0xc985, "V" }, // Ʌ LATIN CAPITAL LETTER TURNED V
    { 0xc986, "E" }, // Ɇ LATIN CAPITAL LETTER E WITH STROKE
    { 0xc987, "e" }, // ɇ LATIN SMALL LETTER E WITH STROKE
    { 0xc988, "J" }, // Ɉ LATIN CAPITAL LETTER J WITH STROKE
    { 0xc989, "j" }, // ɉ LATIN SMALL LETTER J WITH STROKE
    { 0xc98a, "Q" }, // Ɋ LATIN CAPITAL LETTER SMALL Q WITH HOOK TAIL
    { 0xc98b, "q" }, // ɋ LATIN SMALL LETTER Q WITH HOOK TAIL
    { 0xc98c, "R" }, // Ɍ LATIN CAPITAL LETTER R WITH STROKE
    { 0xc98d, "r" }, // ɍ LATIN SMALL LETTER R WITH STROKE
    { 0xc98e, "Y" }, // Ɏ LATIN CAPITAL LETTER Y WITH STROKE
    { 0xc98f, "y" }, // ɏ LATIN SMALL LETTER Y WITH STROKE
    { 0xc990, "a" }, // ɐ LATIN SMALL LETTER TURNED A
    { 0xc993, "b" }, // ɓ LATIN SMALL LETTER B WITH HOOK
    { 0xc994, "o" }, // ɔ LATIN SMALL LETTER OPEN O
    { 0xc995, "c" }, // ɕ LATIN SMALL LETTER C WITH CURL
    { 0xc996, "d" }, // ɖ LATIN SMALL LETTER D WITH TAIL
    { 0xc997, "d" }, // ɗ LATIN SMALL LETTER D WITH HOOK
    { 0xc998, "e" }, // ɘ LATIN SMALL LETTER REVERSED E
    { 0xc99b, "e" }, // ɛ LATIN SMALL LETTER OPEN E
    { 0xc99c, "e" }, // ɜ LATIN SMALL LETTER REVERSED OPEN E
    { 0xc99d, "e" }, // ɝ LATIN SMALL LETTER REVERSED OPEN E WITH HOOK
    { 0xc99e, "e" }, // ɞ LATIN SMALL LETTER CLOSED REVERSED OPEN E
    { 0xc99f, "j" }, // ɟ LATIN SMALL LETTER DOTLESS J WITH STROKE
    { 0xc9a0, "g" }, // ɠ LATIN SMALL LETTER G WITH HOOK
    { 0xc9a1, "g" }, // ɡ LATIN SMALL LETTER SCRIPT G
    { 0xc9a2, "G" }, // ɢ LATIN LETTER SMALL CAPITAL G
    { 0xc9a5, "h" }, // ɥ LATIN SMALL LETTER TURNED H
    { 0xc9a6, "h" }, // ɦ LATIN SMALL LETTER H WITH HOOK
    { 0xc9a8, "i" }, // ɨ LATIN SMALL LETTER I WITH STROKE
    { 0xc9a9, "i" }, // ɩ LATIN SMALL LETTER IOTA
    { 0xc9aa, "i" }, // ɪ LATIN LETTER SMALL CAPITAL I
    { 0xc9ab, "l" }, // ɫ LATIN SMALL LETTER L WITH MIDDLE TILDE
    { 0xc9ac, "l" }, // ɬ LATIN SMALL LETTER L WITH BELT
    { 0xc9ad, "l" }, // ɭ LATIN SMALL LETTER L WITH RETROFLEX HOOK
    { 0xc9af, "m" }, // ɯ LATIN SMALL LETTER TURNED M
    { 0xc9b0, "m" }, // ɰ LATIN SMALL LETTER TURNED M WITH LONG LEG
    { 0xc9b1, "m" }, // ɱ LATIN SMALL LETTER M WITH HOOK
    { 0xc9b2, "n" }, // ɲ LATIN SMALL LETTER N WITH LEFT HOOK
    { 0xc9b3, "n" }, // ɳ LATIN SMALL LETTER N WITH RETROFLEX HOOK
    { 0xc9b4, "n" }, // ɴ LATIN LETTER SMALL CAPITAL N
    { 0xc9b5, "o" }, // ɵ LATIN SMALL LETTER BARRED O
    { 0xc9b6, "o" }, // ɶ LATIN LETTER SMALL CAPITAL OE
    { 0xc9b7, "o" }, // ɷ LATIN SMALL LETTER CLOSED OMEGA
    { 0xc9b9, "r" }, // ɹ LATIN SMALL LETTER TURNED R
    { 0xc9ba, "r" }, // ɺ LATIN SMALL LETTER TURNED R WITH LONG LEG
    { 0xc9bb, "r" }, // ɻ LATIN SMALL LETTER TURNED R WITH HOOK
    { 0xc9bc, "r" }, // ɼ LATIN SMALL LETTER R WITH LONG LEG
    { 0xc9bd, "r" }, // ɽ LATIN SMALL LETTER R WITH TAIL
    { 0xc9be, "r" }, // ɾ LATIN SMALL LETTER R WITH FISHHOOK
    { 0xc9bf, "r" }, // ɿ LATIN SMALL LETTER REVERSED R WITH FISHHOOK
    { 0xca80, "r" }, // ʀ LATIN LETTER SMALL CAPITAL R
    { 0xca81, "R" }, // ʁ LATIN LETTER SMALL CAPITAL INVERTED R
    { 0xca82, "s" }, // ʂ LATIN SMALL LETTER S WITH HOOK
    { 0xca87, "t" }, // ʇ LATIN SMALL LETTER TURNED T
    { 0xca88, "t" }, // ʈ LATIN SMALL LETTER T WITH RETROFLEX HOOK
    { 0xca89, "u" }, // ʉ LATIN SMALL LETTER U BAR
    { 0xca8a, "u" }, // ʊ LATIN SMALL LETTER UPSILON
    { 0xca8b, "v" }, // ʋ LATIN SMALL LETTER V WITH HOOK
    { 0xca8c, "v" }, // ʌ LATIN SMALL LETTER TURNED V
    { 0xca8d, "w" }, // ʍ LATIN SMALL LETTER TURNED W
    { 0xca8e, "y" }, // ʎ LATIN SMALL LETTER TURNED Y
    { 0xca8f, "y" }, // ʏ LATIN LETTER SMALL CAPITAL Y
    { 0xca90, "z" }, // ʐ LATIN SMALL LETTER Z WITH RETROFLEX HOOK
    { 0xca91, "z" }, // ʑ LATIN SMALL LETTER Z WITH CURL
    { 0xca97, "c" }, // ʗ LATIN LETTER STRETCHED C
    { 0xca99, "b" }, // ʙ LATIN LETTER SMALL CAPITAL B
    { 0xca9a, "e" }, // ʚ LATIN SMALL LETTER CLOSED OPEN E
    { 0xca9b, "g" }, // ʛ LATIN LETTER SMALL CAPITAL G WITH HOOK
    { 0xca9c, "h" }, // ʜ LATIN LETTER SMALL CAPITAL H
    { 0xca9d, "j" }, // ʝ LATIN SMALL LETTER J WITH CROSSED-TAIL
    { 0xca9e, "k" }, // ʞ LATIN SMALL LETTER TURNED K
    { 0xca9f, "l" }, // ʟ LATIN LETTER SMALL CAPITAL L
    { 0xcaa0, "q" }, // ʠ LATIN SMALL LETTER Q WITH HOOK
    { 0xcaa3, "d" }, // ʣ LATIN SMALL LETTER DZ DIGRAPH
    { 0xcaa4, "d" }, // ʤ LATIN SMALL LETTER DEZH DIGRAPH
    { 0xcaa5, "d" }, // ʥ LATIN SMALL LETTER DZ DIGRAPH WITH CURL
    { 0xcaa6, "t" }, // ʦ LATIN SMALL LETTER TS DIGRAPH
    { 0xcaa7, "t" }, // ʧ LATIN SMALL LETTER TESH DIGRAPH
    { 0xcaa8, "t" }, // ʨ LATIN SMALL LETTER TC DIGRAPH WITH CURL
    { 0xcaa9, "f" }, // ʩ LATIN SMALL LETTER FENG DIGRAPH
    { 0xcaaa, "l" }, // ʪ LATIN SMALL LETTER LS DIGRAPH
    { 0xcaab, "l" }, // ʫ LATIN SMALL LETTER LZ DIGRAPH
    { 0xcaae, "h" }, // ʮ LATIN SMALL LETTER TURNED H WITH FISHHOOK
    { 0xcaaf, "h" }, // ʯ LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL
    { 0xcb96, "+" }, // ˖ MODIFIER LETTER PLUS SIGN
    { 0xcb97, "-" }, // ˗ MODIFIER LETTER MINUS SIGN
    { 0xcba1, "l" }, // ˡ MODIFIER LETTER SMALL L
    { 0xcba2, "s" }, // ˢ MODIFIER LETTER SMALL S
    { 0xcba3, "x" }, // ˣ MODIFIER LETTER SMALL X
    { 0xcda3, "a" }, // ͣ COMBINING LATIN SMALL LETTER A
    { 0xcda4, "e" }, // ͤ COMBINING LATIN SMALL LETTER E
    { 0xcda5, "i" }, // ͥ COMBINING LATIN SMALL LETTER I
    { 0xcda6, "o" }, // ͦ COMBINING LATIN SMALL LETTER O
    { 0xcda7, "u" }, // ͧ COMBINING LATIN SMALL LETTER U
    { 0xcda8, "c" }, // ͨ COMBINING LATIN SMALL LETTER C
    { 0xcda9, "d" }, // ͩ COMBINING LATIN SMALL LETTER D
    { 0xcdaa, "h" }, // ͪ COMBINING LATIN SMALL LETTER H
    { 0xcdab, "m" }, // ͫ COMBINING LATIN SMALL LETTER M
    { 0xcdac, "r" }, // ͬ COMBINING LATIN SMALL LETTER R
    { 0xcdad, "t" }, // ͭ COMBINING LATIN SMALL LETTER T
    { 0xcdae, "v" }, // ͮ COMBINING LATIN SMALL LETTER V
    { 0xcdaf, "x" }, // ͯ COMBINING LATIN SMALL LETTER X
    { 0xcea3, "\xf6" }, // GREEK CAPITAL LETTER SIGMA
    { 0xcea9, "\xf4" }, // GREEK CAPITAL LETTER OMEGA
    { 0xceb1, "\xe0" }, // GREEK SMALL LETTER ALPHA
    { 0xceb2, "\xe2" }, // GREEK SMALL LETTER BETA
    { 0xceb5, "\xe3" }, // GREEK SMALL LETTER EPSILON
    { 0xcebC, "\xe4" }, // GREEK SMALL LETTER MU
    { 0xcf80, "\xf7" }, // GREEK SMALL LETTER PI
    { 0xcf81, "\xe6" } // GREEK SMALL LETTER RHO
};

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

void sprintf(string &result, const char *format, ...)
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

void utf8_to_hd44780(string &str)
{
    string tmp;
    uint64_t value = 0;
    bool isCompleteCharacter = false;
    for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
    {
        char character = *it;

        if ((character & 0xc0) == 0xc0) // leading byte
        {
            value = (uint64_t)character;
        }
        else if ((character & 0xc0) == 0x80) // sequence byte
        {
            value <<= 8;
            value |= (uint64_t)character;
            if (value > 0xC000 && value < 0xE000) // 2 byte character
            {
                isCompleteCharacter = true;
            }
            else if (value > 0xE00000 && value < 0xF0000000) // 3 byte character
            {
                isCompleteCharacter = true;
            }
            else if (value > 0xF0000000) // 4 byte character
            {
                isCompleteCharacter = true;
            }
        }
        else // single byte character
        {
            // missing in the HD44780 charset
            switch (character)
            {
            case 0x5c : // backslash
                character = '|';
                break;
            case 0x7e : // tilde ~
                character = '-';
                break;
            }
            value = 0;
            isCompleteCharacter = true;
        }
        if (isCompleteCharacter)
        {
            if (value == 0) // single byte character
            {
                tmp.append(1, character);
            }
            else // was UTF-8
            {
                std::unordered_map<uint64_t, string>::const_iterator itMap = characterMapping.find(value);
                if (itMap != characterMapping.end())
                {
                    tmp.append(itMap->second);
                }
                else
                {
                    tmp.append("?"); // unmapped character
                }
            }
            isCompleteCharacter = false;
        }
    }
    str = tmp;
}

} // namespace liblcd

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
