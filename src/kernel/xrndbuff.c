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

process xroundbuff[MAX_THREADS];  //!< The actual circular buffer.
bool    used[MAX_THREADS];        //!< An array of flags indicate which buffer slots are used.

int size    =  0;  //!< Number of defined process structures in the buffer.
int current = -1;  //!< Index in the buffer of "current" process.
int next    = -1;  //!< Index in the buffer of next process to run.

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
    int i = 0;

    // Initialize all pids to unused first time this is called.
    if( size == 0 ) {
        for( i = 0; i < MAX_THREADS; i++ ) {
            xroundbuff[i].pid.pid = -1;
            used[i] = false;
        }
    
        // If the new process is the first process, it is both current and next.
        current = new_proc->pid.pid;
        next = new_proc->pid.pid;
    }

    // Make sure the processID is not in use.
    if( used[new_proc->pid.pid] == false ) {
        xroundbuff[new_proc->pid.pid] = *new_proc;
        used[new_proc->pid.pid] = true;
        size++;
        return 0;	
    }
  
    // 2 processes with same pid!!
    return 1;
}


//! Sets the current process to the last process found by getNext()
void set_current( )
{
    current = next;
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
process* get_current( )
{
    if( current != -1 ) {
        return &xroundbuff[current];
    }
  
    return NULL;
}


//! Returns the process with the given ID.
/*!
 * \param id The process ID of the process to select.
 *  
 * \return A pointer to the process structure for the process with the given ID. If there is no
 * process defined for that ID, this function returns NULL.
 */
process* get_process( processID id )
{ 
    if( used[id.pid] == true ) {
        return &xroundbuff[id.pid];
    }
 
    return NULL;
}


//! Return a pointer to the next defined process.
/*!
 * This function returns a pointer to the next process that is defined in the round buffer. As a
 * side effect it also records this process for use by setCurrent().
 *  
 * \return A pointer to the next defined process. If no processes are defined (for example if
 * addProcess() has not yet been called), this function returns NULL.
 */
process* get_next( )
{
    if( next != -1 ) {
        next++;
    
        // find the next existing process
        while( used[next] == false ) {
            next++;
    
            if( next == MAX_THREADS ) {
                next = 0;
            }
        }
        return &xroundbuff[next];
    }
  
    return NULL;
}
