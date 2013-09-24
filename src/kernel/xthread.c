/****************************************************************************
FILE      : xthread.c
SUBJECT   : Implementation of Phoenix threading.
PROGRAMMER: (C) Copyright 2008  The Phoenix Team.

This file implements Phoenix threading.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Williston, VT 05495
    PChapin@vtc.vsc.edu
****************************************************************************/

#include "xthread.h"
#include "xrndbuff.h"
#include "debug.h"
#include "xstddef.h"

/*! \file xthread.c Thread handling functions.
 *
 * Phoenix uses the terms "process" and "thread" interchangeably. The functions in this file
 * support process/thread creation, management, and synchronization.
 */

#define COLOR 0x04

static word stacks[MAX_THREADS][STACK_SIZE];
static unsigned int lock_counter = 0;
static bool run_idle = false;

// The following function is written in assembly language.
extern void create_process_asm( void *(*start_routine)( void ), word *stack );

// Disable thread and store the current context into stack
int xthread_create( processID id, void *(*start_routine)( void ) )
{
    int     rc = 0;
    process new_process;
  
    new_process.pid = id;
    new_process.runnable = true;
    new_process.stack = stacks[id.pid] + STACK_SIZE;
  
    create_process_asm( start_routine, (word *)new_process.stack );
  
    // This is a bit of a hack. Ideally create_process_asm( ) would take a pointer to the process
    // structure and update its stack member as it is building the initial stack. Right now it
    // is too easy for the line below to get out of sync with what is happening inside create_
    // process_asm().
    //
    new_process.stack -= 12;
  
    if( add_process( &new_process ) != 0 ) rc = 1;
    return rc;
}


//! Marks the specified process as suspended (not runnable).
/*!
 * If the given process ID does not correspond to a defined process, there is no effect. Also
 * suspending an already suspended process has no effect.
 *
 * \param id The process ID of the process to suspend.
 * \return 0 if successful and non-zero if the given ID is invalid.
 */
int xthread_suspend( processID id )
{
    int rc = -1;
    process *current_process;
 
    current_process = get_process( id );
    if( current_process != NULL ) {
        current_process->runnable = false;
        rc = 0;
    }
    return rc;
}


//! Marks the specified process as runnable.
/*!
 * If the given process ID does not correspond to a defined process, there is no effect. Also
 * resuming a runnable process has no effect.
 *
 * \param id The process ID of the process to resume.
 * \return 0 if successful and non-zero if the given ID is invalid.
 */
int xthread_resume( processID id )
{
    int rc = -1;
    process *current_process;
 
    current_process = get_process( id );
    if( current_process != NULL ) {
        current_process->runnable = true;
        rc = 0;
    }
    return rc;
}


//! Initializes an xthread_mutex_t object.
/*!
 * Every xthread_mutex_t must be initialized before it can be used. Although mutexes can be
 * initialized more than once, initializing a mutex that is in active use causes undefined
 * behavior.
 *
 * \param mutex A pointer to the object to be initialized.
 * \return 0 if successful and non-zero if the initialization failed.
 */
int xthread_mutex_init( xthread_mutex_t *mutex )
{
    int i;
  
    mutex->locked = false;
    for( i = 0; i < MAX_THREADS; i++ ) {
        mutex->waiting[i] = false;
    }
    mutex->waiting_index = 0;
  
    return 0;
}


//! Locks an xthread mutex.
/*!
 * Attempts to acquire a lock on the given mutex. If the mutex is already locked the process
 * with the given ID is suspected. Recursive locking is not supported. If a thread attempts
 * to lock a mutex it already has locked, the thread will suspect anyway.
 *
 * \param mutex A pointer to the mutex to lock. The mutex should be initialized.
 * \param proc The process ID of the thread to suspend if the mutex is already locked.
 * \return 0 if successful and non-zero otherwise.
 */
int xthread_mutex_lock( xthread_mutex_t *mutex, processID proc )
{
    int rc = -1;
    
    disable_interrupts( );
    if( mutex->locked == false ) {
        mutex->locked = true;
        mutex->waiting[proc.pid] = false;
        enable_interrupts( );
	
        debug_print( lock_counter++, 39, "u", COLOR );
        rc = 0;
    }
    else {
        xthread_suspend( proc );
        mutex->waiting[proc.pid] = true;
        enable_interrupts( );
	
        debug_print( lock_counter++, 39, "l", COLOR );
        xthread_switch_thread( );
        rc = xthread_mutex_lock( mutex, proc );
    }
    return rc;
}


//! Unlocks an xthread mutex.
/*!
 * Selects exactly one process waiting on the mutex (if any) and resumes it. If no processes
 * are waiting on the mutex, there is no effect.
 *
 * \param mutex A pointer to the mutex to unlock. The mutex must be initialized but it need not
 * be locked.
 * \return 0 if successful and non-zero otherwise.
 */
int xthread_mutex_unlock( xthread_mutex_t *mutex )
{
    processID proc;
    int counter = 0;
  
    // Scan over the waiting list looking for a process that is waiting on this mutex.
    while( mutex->waiting[mutex->waiting_index] != true && counter < MAX_THREADS ) {
        mutex->waiting_index++;
        counter++;
   
        // Wrap the waiting index around when necessary.
        if( mutex->waiting_index == MAX_THREADS ) {
            mutex->waiting_index = 0;
        }
    }
  
    mutex->locked = false;  // If a process was waiting it will immediately relock.
    if( counter != MAX_THREADS ) {
        mutex->waiting[mutex->waiting_index] = false;
        proc.pid = mutex->waiting_index;
        xthread_resume( proc );
    }
    return 0;
}


int xthread_cond_init( xthread_cond_t *cond )
{
    int i = 0;

    for( i = 0; i < MAX_THREADS; i++ ) {
        cond->waiting[i] = false;
    }
    cond->waiting_index = 0;
    return 0;
}


int xthread_cond_wait( xthread_cond_t *cond, xthread_mutex_t *mutex, processID proc )
{
    disable_interrupts( );
    xthread_mutex_unlock( mutex );
    cond->waiting[proc.pid] = true;
    xthread_suspend( proc );
    enable_interrupts( );
    xthread_switch_thread( );
    xthread_mutex_lock( mutex, proc );
    return 0;
}


int xthread_cond_signal( xthread_cond_t *cond )
{
    processID proc;
    int counter = 0;
  
    // check for people waiting
    while( cond->waiting[cond->waiting_index] != true && counter < MAX_THREADS ) {
        cond->waiting_index++;
        counter++;
    
        if( cond->waiting_index == MAX_THREADS ) {
            cond->waiting_index = 0;
        }
    }
  
    // if we found someone waiting
    if( counter != MAX_THREADS ) {
        proc.pid = cond->waiting_index;
	
        // remove from waiting list
        cond->waiting[proc.pid] = false;
	
        // make them runnable
        xthread_resume( proc );
        return 1;
    }
    return 0;
}


void disable_interrupts( )
{
    debug_print( lock_counter++, 40, "d", COLOR );
    _asm {
        CLI
    };
}


void enable_interrupts( )
{
    debug_print( lock_counter++, 40, "e", COLOR );
    _asm {
        STI
    };
}


void xthread_switch_thread( )
{
    _asm {
        int 08h
    };
}
