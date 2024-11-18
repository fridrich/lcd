## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-


if WITH_TOOLS

bin_PROGRAMS = lcd_test

AM_CXXFLAGS = \
	-I$(top_srcdir)/inc \
	$(LIBLCD_CXXFLAGS) \
	$(DEBUG_CXXFLAGS)

lcd_test_LDADD = \
	../lib/liblcd-@LCD_MAJOR_VERSION@.@LCD_MINOR_VERSION@.la \
	$(LIBLCD_LIBS)

lcd_test_SOURCES = \
	lcd_test.cpp

EXTRA_DIST = \
	$(lcd_test_SOURCES)

endif

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
