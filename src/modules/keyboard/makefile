############################################################################
# FILE        : makefile
# LAST REVISED: 2008-03-13
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the keyboard module.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -bt=dos -fo=$[*.obj -I../../RTL -I../../kernel $[*.c

OBJ=keyboard.obj kparser.obj

keyboard.lib: $(OBJ)
    wlib -q -n keyboard.lib @<<keyboard.lbc 
+kparser.obj
+keyboard.obj
<<

clean: .SYMBOLIC
    rm -f *.obj *.err keyboard.lib
