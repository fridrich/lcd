## -*- Mode: make; tab-width: 4; indent-tabs-mode: tabs -*-

if PLATFORM_WIN32
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -avoid-version
else
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
endif

lib_LTLIBRARIES = liblcd-@LCD_MAJOR_VERSION@.@LCD_MINOR_VERSION@.la
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_includedir = $(includedir)/liblcd-@LCD_MAJOR_VERSION@.@LCD_MINOR_VERSION@/liblcd
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_include_HEADERS = \
	$(top_srcdir)/inc/liblcd/LCDDisplay.h \
	$(top_srcdir)/inc/liblcd/liblcd.h

AM_CXXFLAGS = \
	-DLIBLCD_BUILD=1 \
	-I$(top_srcdir)/inc \
	$(DEBUG_CXXFLAGS)

liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_LIBADD = \
	@LIBLCD_WIN32_RESOURCE@

liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_DEPENDENCIES = @LIBLCD_WIN32_RESOURCE@
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic -no-undefined
liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_SOURCES = \
	LCDDisplay.cpp \
	liblcd_utils.cpp \
	liblcd_utils.h

if OS_WIN32

@LIBLCD_WIN32_RESOURCE@ : liblcd.rc $(liblcd_@LCD_MAJOR_VERSION@_@LCD_MINOR_VERSION@_la_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource liblcd.rc @LIBLCD_WIN32_RESOURCE@

endif

EXTRA_DIST = \
	liblcd.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	liblcd.rc

## vim:set shiftwidth=4 tabstop=4 noexpandtab:
