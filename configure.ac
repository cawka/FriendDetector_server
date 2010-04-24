#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT("FriendDetector_Server", "0.0", "alexander.afanasyev@ucla.edu")
AC_CANONICAL_SYSTEM

AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL


AC_ARG_WITH([opencv],
	[AS_HELP_STRING([--with-opencv=<path>],[specify path for opencv installation @<:@default=/usr/local@:>@])],
	[with_opencv=$withval],
	[with_opencv=/usr/local])

AC_ARG_WITH([ice],
	[AS_HELP_STRING([--with-ice=<path>],[specify path for Ice installation @<:@default=/opt/local@:>@])],
	[with_ice=$withval],
	[with_ice=/opt/local])


OPENCV_INCLUDE="-I$with_opencv/include"
OPENCV_LIB="-L$with_opencv/lib"

ICE_INCLUDE="-I$with_ice/include"
ICE_LIB="-L$with_ice/lib"

ICE_EXTRA=""

case "$host_os" in
    linux*)
        OS=linux ;;
    darwin*)
		ICE_EXTRA="-lZeroCIce"
        OS=darwin;;
#    gnu*)
#        OS=gnu ;;
#    bsdi*)
#        OS=bsdi;;
#    *mingw32*)
#        OS=mingw32;;
    *)
        AC_MSG_ERROR([unknown or unsupported OS $host_os.  Only Linux and MacOSX (darwin) are supported.]);;
esac

AC_SUBST(OS)

AC_SUBST(ICE_INCLUDE)
AC_SUBST(ICE_LIB)
AC_SUBST(ICE_EXTRA)

AC_SUBST(OPENCV_INCLUDE)
AC_SUBST(OPENCV_LIB)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

