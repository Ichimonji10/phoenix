/****************************************************************************
FILE          : xrndbuff.c
LAST REVISION : 2008-02-5
SUBJECT       : Phoenix main round buffer.
PROGRAMMER    : (C) Copyright 2008 by The Phoenix Contributors.

This file defines the Phoenix round buffer for switching processes.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

/*! \file xrndbuff.c Circular buffer holding process information.
 *
 * This file contains the functions used for manipulating a circular buffer of
 * process information structures.
 */

#include "xrndbuff.h"
#include "xstddef.h"
#include "types.h"

process xroundbuff[MAX_THREADS]; //!< A circular buffer of process info structs
bool used[MAX_THREADS]; //!< Flags indicating which ringbuffer slots are used.
int size    =  0;  //!< Number of defined process structures in the buffer.
int current = -1;  //!< Buffer index of currently selected process.

// Check whether process `id` exists in the roundbuffer.
//
// \return true if `id.pid` is sane and a the corresponding roundbuffer location
// is in use.
bool _process_exists( processID id ) {
    int index = id.pid;
    if( index < 0 || index >= MAX_THREADS || false == used[index] ) {
        return false;
    }
    return true;
}

//! Add a process to the round buffer.
/*!
 * Insert process structure `new_proc` into the round buffer. This allows the
 * process to be scheduled to run. The process structure must already be
 * initialized or undefined behaviour will occur. The first time this function
 * is called, the internal roundbuffer index will be initialized to point at
 * that process.
 *
 * This function is not thread-safe. Do not call it from more than one thread at
 * a time!
 *
 * \param new_proc A pointer to the process structure to add.
 *
 * \return Zero on success. Non-zero if the process ID of the new process is
 * already in use by an existing process, less than zero or greater than
 * `MAX_THREADS`.
 */
int add_process( process *new_proc )
{
    int i;

    // Do some extra work when the first process is created.
    if( 0 == size ) {
        for( i = 0; i < MAX_THREADS; i++ ) {
            xroundbuff[i].pid.pid = -1;
            used[i] = false;
        }
        // The first process in the ringbuffer is the current process
        current = new_proc->pid.pid;
    }

    // Throw an error if `new_proc` has the same ID as an existing process.
    if( true == used[new_proc->pid.pid] ) { return 1; }

    xroundbuff[new_proc->pid.pid] = *new_proc;
    used[new_proc->pid.pid] = true;
    size++;
    return 0;
}


//! Make the ringbuffer index point to the process with id `id`.
/*!
 * \param id The process ID of the process to point to.
 *
 * \return true on success, else false.
 */
bool set_current( processID id ) {
    if( false == _process_exists(id) ) { return false; }
    current = id.pid;
    return true;
}


//! Return the currently selected process.
/*!
 * \return A pointer to the process structure for the current process. If there
 * is no current process selected (e.g. if addProcess() has never been called),
 * return NULL.
 */
process *get_current( )
{
    if( -1 == current ) { return NULL; }
    return &xroundbuff[current];
}


//! Return the process with ID `id`.
/*!
 * \param id The process ID of the process to select.
 *  
 * \return A pointer to the process structure for the process with the given ID.
 * Return NULL if there is no process defined for that ID.
 */
process *get_process( processID id )
{ 
    if( false == _process_exists(id) ) { return NULL; }
    return &xroundbuff[id.pid];
}


//! Return a pointer to the next defined process.
/*!
 * Select the next defined process in the round buffer and return a pointer to
 * that process.
 *  
 * \return A pointer to the next defined process. Return `NULL` if no processes
 * are defined (e.g. `add_process()` has never been called).
 */
process * get_next( processID id )
{
    int pid = id.pid;
    if( false == _process_exists(id) ) { return NULL; }

    do {
        pid = ( pid + 1 ) % MAX_THREADS;
        if( used[pid] ) { return &xroundbuff[pid]; }
    } while( pid != id.pid );
    return NULL;
}
