dnl -*- Mode: Autoconf; tab-width: 4; indent-tabs-mode: nil; fill-column: 102 -*-
# Process this file with autoconf to create configure.

AC_PREREQ([2.72])

# ====================
# Version informations
# ====================
m4_define([liblcd_version_major],[0])
m4_define([liblcd_version_minor],[0])
m4_define([liblcd_version_micro],[0])
m4_define([liblcd_version],[liblcd_version_major.liblcd_version_minor.liblcd_version_micro])

# =============
# Automake init
# =============
AC_INIT([liblcd],[liblcd_version])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11 foreign dist-xz dist-bzip2])
AM_SILENT_RULES([yes])
AC_LANG([C++])

# ===========================
# Find required base packages
# ===========================
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT([win32-dll disable-static pic-only])
AC_CANONICAL_HOST

AX_CXX_COMPILE_STDCXX_11
AX_GCC_FUNC_ATTRIBUTE([format])
DLP_FALLTHROUGH

# =================================
# Libtool/Version Makefile settings
# =================================
AC_SUBST(LCD_MAJOR_VERSION, [liblcd_version_major])
AC_SUBST(LCD_MINOR_VERSION, [liblcd_version_minor])
AC_SUBST(LCD_MICRO_VERSION, [liblcd_version_micro])
AC_SUBST(LCD_VERSION, [liblcd_version])
# AC_SUBST(LT_RELEASE, [liblcd_version_major.liblcd_version_minor])
LT_CURRENT=`expr 100 '*' liblcd_version_major + liblcd_version_minor`
# For 1.0.0 comment the first line and uncomment the second
LT_AGE=0
# LT_AGE=liblcd_version_minor
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION, [liblcd_version_micro])
AC_SUBST(LT_AGE)

# ==========================
# Platform check for windows
# ==========================
AC_MSG_CHECKING([for native Win32])
AS_CASE([$host],
    [*-*-mingw*], [
        native_win32=yes
        LIBLCD_WIN32_RESOURCE=liblcd-win32res.lo
        
    ], [
        native_win32=no
        LIBLCD_WIN32_RESOURCE=
        
    ]
)
AC_MSG_RESULT([$native_win32])
AM_CONDITIONAL(OS_WIN32, [test "x$native_win32" = "xyes"])
AC_SUBST([LIBLCD_WIN32_RESOURCE])


AC_MSG_CHECKING([for Win32 platform in general])
AS_CASE([$host],
    [*-*-mingw*|*-*-cygwin*], [platform_win32=yes],
    [platform_win32=no]
)
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL([PLATFORM_WIN32], [test "x$platform_win32" = "xyes"])

AS_IF([test "x$platform_win32" = "xyes"],
    [],
    [
        AC_MSG_CHECKING([for -fvisibility=hidden compiler flag])
        saved_CXXFLAGS="$CXXFLAGS"
        CXXFLAGS="$CXXFLAGS -fvisibility=hidden"
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[]])],[
                AC_MSG_RESULT([yes])
                CXXFLAGS="$CXXFLAGS -DLIBLCD_VISIBILITY"
            ],[
                AC_MSG_RESULT([no])
                CXXFLAGS="$saved_CXXFLAGS"
            
        ])
    ]
)

# ================
# Check for cflags
# ================
AC_ARG_ENABLE([werror],
    [AS_HELP_STRING([--enable-werror], [Treat all warnings as errors, usefull for development])],
    [enable_werror="$enableval"],
    [enable_werror=no]
)
AS_IF([test x"$enable_werror" != "xno"], [
    CFLAGS="$CFLAGS -Werror"
    CXXFLAGS="$CXXFLAGS -Werror"
])
AC_ARG_ENABLE([weffc],
    [AS_HELP_STRING([--disable-weffc], [ Disable -Weffc++ warnings, usefull when using an old version of gcc or of boost])],
    [enable_weffc="$enableval"],
    [enable_weffc=yes]
)
AC_ARG_ENABLE([wparanoic],
    [AS_HELP_STRING([--enable-wparanoic], [Enable a lot of warnings...])],
    [enable_wparanoic="$enableval"],
    [enable_wparanoic=no]
)
# Courtesy of Glib: Ensure MSVC-compatible struct packing convention
# is used when compiling for Win32 with gcc.
AS_IF([test "x$native_win32" = "xyes"], [
    AC_CHECK_TOOL(WINDRES, windres)
    AS_IF([test x"$GCC" = xyes], [
        AC_MSG_CHECKING([how to get MSVC-compatible struct packing])
        AS_IF([test -z "$ac_cv_prog_CC"], [
            our_gcc="$CC"
        ], [
            our_gcc="$ac_cv_prog_CC"
        ])
        AS_IF([$our_gcc -v --help 2>/dev/null | grep ms-bitfields >/dev/null], [
            msnative_struct="-mms-bitfields"
            CFLAGS="$CFLAGS $msnative_struct"
            CXXFLAGS="$CXXFLAGS $msnative_struct"
            AC_MSG_RESULT([${msnative_struct}])
        ], [
            AC_MSG_RESULT([no way])
            AC_MSG_WARN([produced libraries might be incompatible with MSVC-compiled code])
        ])
    ])
    CFLAGS="$CFLAGS -Wall -Wextra -pedantic"
    CXXFLAGS="$CXXFLAGS -Wall -Wextra -Wshadow -pedantic"
], [
    AS_IF([test x"$GCC" = xyes], [
        # Be tough with warnings and produce less careless code
        CFLAGS="$CFLAGS -Wall -Wextra -pedantic"
        CXXFLAGS="$CXXFLAGS -Wall -Wextra -pedantic -Wshadow -Wunused-variable"
        AS_IF([test x"$enable_weffc" != "xno"], [
            CXXFLAGS="$CXXFLAGS -Weffc++"
        ])
        AS_IF([test x"$enable_wparanoic" != "xno"], [
            CXXFLAGS="$CXXFLAGS -Wcast-align -Wcast-qual -Wchar-subscripts"
            CXXFLAGS="$CXXFLAGS -Wcomment -Wconversion -Wdisabled-optimization"
            CXXFLAGS="$CXXFLAGS -Wfloat-equal -Wformat -Wformat=2"
            CXXFLAGS="$CXXFLAGS -Wformat-nonliteral -Wformat-security"
            CXXFLAGS="$CXXFLAGS -Wformat-y2k -Wimport -Winit-self -Winvalid-pch"
            CXXFLAGS="$CXXFLAGS -Wmissing-braces -Wmissing-field-initializers"
            CXXFLAGS="$CXXFLAGS -Wmissing-format-attribute -Wmissing-include-dirs"
            CXXFLAGS="$CXXFLAGS -Wmissing-noreturn -Wpacked -Wparentheses"
            CXXFLAGS="$CXXFLAGS -Wpointer-arith -Wredundant-decls -Wreturn-type"
            CXXFLAGS="$CXXFLAGS -Wsequence-point -Wsign-compare -Wstrict-aliasing"
            CXXFLAGS="$CXXFLAGS -Wstrict-aliasing=2 -Wswitch -Wswitch-default"
            CXXFLAGS="$CXXFLAGS -Wswitch-enum -Wtrigraphs -Wunknown-pragmas -Wunused"
            CXXFLAGS="$CXXFLAGS -Wunused-function -Wunused-label -Wunused-parameter"
            CXXFLAGS="$CXXFLAGS -Wunused-value -Wvariadic-macros"
            CXXFLAGS="$CXXFLAGS -Wvolatile-register-var -Wwrite-strings"
        ])
    ])
])
AC_SUBST(DEBUG_CXXFLAGS)

# ============
# Debug switch
# ============
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug], [Turn on debugging])],
    [enable_debug="$enableval"],
    [enable_debug=no]
)
AS_IF([test "x$enable_debug" = "xyes"], [
    DEBUG_CXXFLAGS="-DDEBUG -g"
    CXXFLAGS="$CXXFLAGS -O0"
    CFLAGS="$CFLAGS -O0"
], [
    DEBUG_CXXFLAGS="-DNDEBUG"
])
AC_SUBST(DEBUG_CXXFLAGS)

# ==================
# Command-line tools
# ==================
AC_ARG_WITH(tools,
    [AS_HELP_STRING([--without-tools], [Do not build command-line tools])],
    [with_tools="$withval"],
    [AS_IF([test "x$native_win32" = "xyes"], [with_tools=no], [with_tools=yes])]
)
AM_CONDITIONAL([WITH_TOOLS], [test "x$with_tools" != "xno"])

# =====================
# Prepare all .in files
# =====================
AC_CONFIG_FILES([
Makefile
inc/Makefile
inc/liblcd/Makefile
src/Makefile
src/tools/Makefile
src/lib/Makefile
src/lib/liblcd.rc

liblcd-$LCD_MAJOR_VERSION.$LCD_MINOR_VERSION.pc:liblcd.pc.in
])
AC_OUTPUT

# ==============================================
# Display final informations about configuration
# ==============================================
AC_MSG_NOTICE([
==============================================================================
Build configuration:
    debug:           ${enable_debug}
    tools:           ${with_tools}
    werror:          ${enable_werror}
==============================================================================
])

dnl vim:set shiftwidth=4 softtabstop=4 expandtab:
