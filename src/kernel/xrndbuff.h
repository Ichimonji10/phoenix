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
 * index is initialized which points to the location of the new process in the
 * ringbuffer. Subsequent calls to `add_process()` do not affect the index.
 *
 * Only `add_process()` and `set_current()` affect the index. See the function
 * definitions for more details.
 */

#ifndef XROUNDBUFF_H
#define XROUNDBUFF_H

#include "xthread.h"

int  add_process( process * );
bool set_current( processID );

process *get_current( );
process *get_process( processID );
process *get_next( processID );

#endif
