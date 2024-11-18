## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

lib_LTLIBRARIES = liblcd-@LCD_MAJOR_VERSION@.@LCD_MINOR_VERSION@.la
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_includedir = $(includedir)/liblcd-@LCD_MAJOR_VERSION@.@LCD_MINOR_VERSION@/liblcd
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_include_HEADERS = \
	$(top_srcdir)/inc/liblcd/LCDDisplay.h \
	$(top_srcdir)/inc/liblcd/liblcd.h

AM_CXXFLAGS = \
	-DLIBLCD_BUILD=1 \
	-I$(top_srcdir)/inc \
	$(DEBUG_CXXFLAGS)

liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic -no-undefined
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_SOURCES = \
	LCDDisplay.cpp \
	liblcd_utils.cpp \
	liblcd_utils.h

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
