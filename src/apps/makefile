############################################################################
# FILE        : makefile
# AUTHOR      : Phoenix Contributors
#
# This is the makefile for the test applications.
############################################################################

.c.obj: .AUTODEPEND
    wcc -q -ms -s -w4 -wcd201 -bt=dos -fo=$[*.obj -I../RTL -I../kernel -I../modules/video -I../modules/keyboard -I../modules/audio -I../modules/gamepad $[*.c

.asm.obj:
    wasm -fo=$[*.obj $[*.asm

all: test_01.exe   &
     test_02.exe   &
     testMtx.exe   &
     superMtx.exe  &
     testCond.exe  &
     test_key.exe  &
     fishtest.exe  &
     breakout.exe  &
     bounce.exe    &
     bascTest.exe  &
     graptest.exe  &
     gpadtest.exe  &
     beepTest.exe  &
     runAnim.exe

test_01.exe: startup.obj test_01.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name test_01.exe
file startup.obj
file test_01.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

test_02.exe: startup.obj test_02.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name test_02.exe
file startup.obj
file test_02.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
library ../modules/keyboard/keyboard.lib
<<

testMtx.exe: startup.obj testMtx.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name testMtx.exe
file startup.obj
file testMtx.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

superMtx.exe: startup.obj superMtx.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name superMtx.exe
file startup.obj
file superMtx.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

testCond.exe: startup.obj testCond.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name testCond.exe
file startup.obj
file testCond.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

test_key.exe: startup.obj test_keyboard.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name test_key.exe
file startup.obj
file test_keyboard.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
library ../modules/keyboard/keyboard.lib
<<

prngtest.exe: startup.obj prngtest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name prngtest.exe
file startup.obj
file prngtest.obj
library ../modules/video/video.lib
library ../kernel/kernel.lib
library ../RTL/RTL.lib
<<

fishtest.exe: startup.obj fishtest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name fishtest.exe
file startup.obj
file fishtest.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

breakout.exe: startup.obj breakout.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name breakout.exe
file startup.obj
file breakout.obj
library ../RTL/RTL.lib
library ../modules/video/video.lib
library ../modules/keyboard/keyboard.lib
library ../modules/audio/audio.lib
<<

bounce.exe: startup.obj bounce.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name bounce.exe
file startup.obj
file bounce.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
library ../modules/keyboard/keyboard.lib
library ../modules/audio/audio.lib
<<

bascTest.exe: startup.obj bascTest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name bascTest.exe
file startup.obj
file bascTest.obj
library ../RTL/RTL.lib
library ../modules/video/video.lib
<<

graptest.exe: startup.obj graptest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name graptest.exe
file startup.obj
file graptest.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
<<

beepTest.exe: startup.obj beepTest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name beepTest.exe
file startup.obj
file beepTest.obj
library ../RTL/RTL.lib
library ../modules/audio/audio.lib
<<

gpadtest.exe: startup.obj gpadtest.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name gpadtest.exe
file startup.obj
file gpadtest.obj
library ../RTL/RTL.lib
library ../modules/gamepad/gamepad.lib
library ../modules/video/video.lib
<<

runAnim.exe: startup.obj runAnim.obj
    wlink @<<link.rsp
option quiet
option NODEFAULTLIBS
system dos
name runAnim.exe
file startup.obj
file runAnim.obj
library ../RTL/RTL.lib
library ../kernel/kernel.lib
library ../modules/video/video.lib
library ../modules/keyboard/keyboard.lib
library ../modules/audio/audio.lib
<<

clean: .SYMBOLIC
    rm -f *.obj *.err *.exe

