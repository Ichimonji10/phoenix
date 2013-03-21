############################################################################
# FILE        : makefile
# LAST REVISED: 2008-01-30
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the run-time library.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -bt=dos -fo=$[*.obj $(DEBUG) -I../modules/video -I../modules/keyboard -I../kernel $[*.c

OBJ=xstring.obj debug.obj xvideo.obj xkeyboard.obj

RTL.lib: $(OBJ)
    wlib -q -n RTL.lib @<<RTL.lbc 
+xstring.obj
+debug.obj
+xvideo.obj
+xkeyboard.obj
<<

clean: .SYMBOLIC
    rm -f *.obj *.err RTL.lib



