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

/*! \file xrndbuff.h Circular buffer holding process information.
 *
 * A ringbuffer is used to store information about processes, and the functions
 * defined here are used to interact with that ringbuffer. The ringbuffer is of
 * a fixed size, and each process fills one element of that ringbuffer.
 * Therefore, not all elements of the ringbuffer are filled with useful
 * information at all times.
 *
 * `add_process()` should be called before any other function, or else undefined
 * behaviour will occur. When `add_process()` is called for the first time, an
 * index is initialized which points to that process in the ringbuffer. Other
 * functions in this file (e.g. `get_next()`) make use of the index. The word
 * "current" (like in `get_current()`) refers to the process being pointed to by
 * the index.
 *
 * The index is maintained internally, and users of this library should not
 * manipulate it.
 */

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
