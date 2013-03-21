/****************************************************************************
FILE          : keyboard.h
LAST REVISION : 2008-03-06
SUBJECT       : Keyboard interface.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This module initialize the keyboard interface

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#ifndef KEYBOARD_INTERFACE_H
#define KEYBOARD_INTERFACE_H

#include "types.h"

#define KeyboardISR 0x09

extern int count;

void __interrupt __far keyboard_ISR();
void initialize_keyboardISR();
char *getKeyString();
char getKey();
char *getNewkeys();
int getNewkeys_size();
bool hasRead();
void finishRead();

#endif

