############################################################################
# FILE        : makefile
# LAST REVISED: 2008-01-30
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the video module.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -bt=dos -fo=$[*.obj -I../../RTL -I../../kernel $[*.c

OBJ=images.obj vga.obj video.obj vparser.obj

video.lib: $(OBJ)
    wlib -q -n video.lib @<<video.lbc 
+images.obj
+vga.obj
+video.obj
+vparser.obj
<<

clean: .SYMBOLIC
    rm -f *.obj *.err video.lib



