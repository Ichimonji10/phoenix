/****************************************************************************
FILE          : xtimer.h
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix message passing.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This file defines the interface to the Phoenix message passing system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include <conio.h>

#ifndef XTIMER_H
#define XTIMER_H

#define LOW_BYTE(n) (n & 0x00FF)
#define HIGH_BYTE(n) ((n >> 8) & 0x00FF)
#define TimerIRQ 0x08

void initialize_timerISR( );
void initialize_timer_frequency( );
void reset_timer_interrupt( );
unsigned int get_random( );

#endif

