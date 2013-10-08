############################################################################
# FILE        : makefile
# LAST REVISED: 2008-02-02
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the kernel.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -bt=dos -fo=$[*.obj -I../RTL -I../modules/video $[*.c
    
.asm.obj:
    wasm -q -fo=$[*.obj $[*.asm

OBJ=message.obj xbuffer.obj xrndbuff.obj xthread.obj xt_asm.obj xtimer.obj

kernel.lib: $(OBJ)
    wlib -q -n kernel.lib @<<kernel.lbc 
+message.obj
+xbuffer.obj
+xrndbuff.obj
+xthread.obj
+xt_asm.obj
+xtimer.obj
<<

clean: .SYMBOLIC
    rm -f *.obj *.o *.err *.exe *.lib *.bak

