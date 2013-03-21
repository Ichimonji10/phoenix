############################################################################
# FILE        : makefile
# LAST REVISED: 2008-02-14
# AUTHOR      : (C) Copyright 2008 by Phoenix Contributors
#
# This is the makefile for the tools.
############################################################################

!ifdef __MSDOS__
CC = wcc
PLATFORM_OPTIONS = -bt=dos
LIBPATH = /home/peter/local/watcom/lib286/dos
LIBRARY = clibs.lib
!else
CC = wcc386
PLATFORM_OPTIONS = -bt=nt
LIBPATH = /home/peter/local/watcom/lib386/nt
LIBRARY = clib3r.lib
!endif

.c.obj: .AUTODEPEND
    $(CC) -q -w4 -fo=$[*.obj $(PLATFORM_OPTIONS) $[*.c
    
all:    bmp2hex.exe memalign.exe

bmp2hex.exe: bmp2hex.obj
    wlink @<<link.rsp
option quiet
system nt
libpath $(LIBPATH)
library $(LIBRARY)
name bmp2hex.exe
file bmp2hex.obj
<<

memalign.exe: memalign.obj
    wlink @<<link.rsp
option quiet
system nt
libpath $(LIBPATH)
library $(LIBRARY)
name memalign.exe
file memalign.obj
<<

clean: .SYMBOLIC
    rm -f *.obj *.err bmp2hex.exe memalign.exe
