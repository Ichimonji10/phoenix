#!/usr/bin/env bash
#
# Contributor: Marcel Deslauriers
# Contributor: Jeremy "Ichimonji10" Audet <ichimonji10 at gmail dot com>
#
# Create a Phoenix boot image and start bochs.
#

set -o errexit
set -o nounset
readonly script_name='makeandrun.sh'
readonly usage="usage: $script_name <rootdir>

$script_name generates a Phoenix boot image and starts bochs. Open Watcom
environment variables (e.g. WATCOM and EDPATH) must be set for this script to
succeed. (if using VTC's hackbox, run 'source useOW')

<rootdir>
    The root directory of the Phoenix source code."

# Fetch argument from user and set `rootdir`.
# Do not set a default `rootdir`. See: http://mywiki.wooledge.org/BashFAQ/028
if [ -z "${1:-}" ]; then
    echo "$usage"
    exit 1
else
    readonly rootdir="`readlink -e "$1"`"
fi
# mtoolsrc specifies location of a: (floppy) drive
export MTOOLSRC="$rootdir"/images/mtoolsrc

#=======================================

cd "$rootdir"/src
wmake

cd "$rootdir"/src/tools
wcl386 memalign.c
wcl386 copyboot.c

cd "$rootdir"/src/boot
nasm boot.asm -o boot.bin

cd "$rootdir"/images
dd if=/dev/zero of=floppy.img count=2880
mformat a:
../src/tools/copyboot ../src/boot/boot.bin floppy.img

cd "$rootdir"/src/boot
wmake
../tools/memalign loader.com

cd "$rootdir"/images
mcopy ../src/boot/bloader.com a:BLOADER.COM
mcopy ../src/apps/test_01.exe a:TEST_01.EXE
mcopy ../src/apps/test_02.exe a:TEST_02.EXE
mcopy ../src/apps/breakout.exe a:BREAKOUT.EXE
mcopy ../src/apps/beepTest.exe a:BEEPTEST.EXE
mcopy ../src/apps/runAnim.exe a:RUNANIM.EXE
mcopy ../src/apps/bounce.exe a:BOUNCE.EXE
bochs -f Phoenix.bxrc
