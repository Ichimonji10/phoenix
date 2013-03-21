############################################################################
# FILE        : makefile
# LAST REVISED: 2008-03-13
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the stage 2 bootloader.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -wcd201 -bt=dos -fo=$[*.obj -I../RTL $[*.c

all: loader.com

loader.com: loader.obj
    wlink @<<link.rsp
option quiet
option map
system com
libpath /home/peter/local/watcom/lib286/dos
library clibs.lib   # Eventually this should not be needed.
name loader.com
file loader.obj
library ../RTL/RTL.lib
<<

clean: .SYMBOLIC
    rm -f *.obj *.err *.exe



