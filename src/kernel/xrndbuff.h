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
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#ifndef XROUNDBUFF_H
#define XROUNDBUFF_H

#include "xthread.h"

int  addProcess( process * );
void setCurrent( );
void setIdle( );

process *getCurrent( );
process *getProcess( processID );
process *getNext( );

#endif
