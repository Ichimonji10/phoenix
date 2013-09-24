/****************************************************************************
FILE          : xrndbuff.h
LAST REVISION : 2008-03-13
SUBJECT       : Phoenix main round buffer.
PROGRAMMER    : (C) Copyright 2008 by The Phoenix Contributors

This header file specifies the Phoenix round buffer for switching processes.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Williston, VT 05495
    PChapin@vtc.vsc.edu
****************************************************************************/

#ifndef XROUNDBUFF_H
#define XROUNDBUFF_H

#include "xthread.h"

int  add_process( process * );
void set_current( );
void set_idle( );

process *get_current( );
process *get_process( processID );
process *get_next( );

#endif
