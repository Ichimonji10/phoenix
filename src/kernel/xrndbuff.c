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

#include "xrndbuff.h"
#include "xstddef.h"
#include "types.h"

/*! \file xrndbuff.c Circular buffer holding process information.
 *
 * This file contains the functions used for manipulating a circular buffer of process
 * information structures. Whenever a new process needs to be scheduled for execution, the
 * "next" runnable entry in the round buffer is used.
 */

process xroundbuff[MAX_THREADS]; //!< A circular buffer of process info structs
bool used[MAX_THREADS]; //!< Flags indicating which ringbuffer slots are used.
int size    =  0;  //!< Number of defined process structures in the buffer.
int current = -1;  //!< Buffer index of currently selected process.

//! Add a process to the round buffer.
/*!
 * This function inserts an already initialized process structure into the round buffer (so that
 * the process can potentially be scheduled for running). The first time this function is
 * called, some additional initialization activities are done. Note that this function is not
 * thread-safe. Do not call it from more than one thread at a time!
 *  
 * \param new_proc A pointer to the initialized process structure to add.
 *  
 * \return Zero if there is no error; non-zero otherwise. If the process ID of the new process
 * is already in use by an existing process, this function returns an error indication.
 */
int add_process( process *new_proc )
{
    int i;

    // Initialize all pids to unused first time this is called.
    if( 0 == size ) {
        for( i = 0; i < MAX_THREADS; i++ ) {
            xroundbuff[i].pid.pid = -1;
            used[i] = false;
        }
        // The first process in the ringbuffer is the current process
        current = new_proc->pid.pid;
    }

    // Throw an error if `new_proc` has the same ID as an existing process.
    if( true == used[new_proc->pid.pid] ) {
        return 1;
    }

    xroundbuff[new_proc->pid.pid] = *new_proc;
    used[new_proc->pid.pid] = true;
    size++;
    return 0;
}


void set_idle( )
{
    current = 0;
}


//! Returns the currently "selected" process.
/*!
 * \return A pointer to the process structure for the current process. If there is no current
 * process selected (for example if addProcess() has never been called), this function returns
 * NULL.
 */
process *get_current( )
{
    if( -1 == current ) { return NULL; }
    return &xroundbuff[current];
}


//! Returns the process with the given ID.
/*!
 * \param id The process ID of the process to select.
 *  
 * \return A pointer to the process structure for the process with the given ID. If there is no
 * process defined for that ID, this function returns NULL.
 */
process *get_process( processID id )
{ 
    // The value of id.pid should never be out of range. Protecting against undefined behavior.
    if( id.pid < 0 || id.pid >= MAX_THREADS || false == used[id.pid] ) {
        return NULL;
    }
    return &xroundbuff[id.pid];
}


//! Return a pointer to the next defined process.
/*!
 * This function returns a pointer to the next process that is defined in the round buffer. As a
 * side effect it also records this process for use by set_current().
 *  
 * \return A pointer to the next defined process. If no processes are defined (for example if
 * add_process() has not yet been called), this function returns NULL.
 */
process *get_next( )
{
    if( -1 == current ) { return NULL; }

    do {
        current = (current + 1) % MAX_THREADS;
    } while( false == used[current] );
    return &xroundbuff[current];
}
