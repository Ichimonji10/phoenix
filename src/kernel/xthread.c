/****************************************************************************
FILE          : xthread.c
LAST REVISION : 2008-01-24
SUBJECT       : Implemenation of Phoenix threading.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This file implements Phoenix threading.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xthread.h"
#include "xrndbuff.h"
#include "debug.h"
#include "xstddef.h"

/*! \file xtrhead.c Thread handling functions.
 *
 * When you figure out what these functions do, document them here.
 */

#define COLOR 0x04

word stacks[MAX_THREADS][STACK_SIZE];
unsigned int lock_counter = 0;
bool run_idle = false;

extern void create_process_asm( void *(*start_routine)( void ), word *stack );
extern void next_process_asm( word *stack );

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
  
    if( add_process(&new_process) != 0 ) rc = 1;
    return rc;
}


// Stored all the register value than suspend the current thread, after the thread suspended the
// next runnable thread will be called.
//
int xthread_suspend( processID id )
{
    process *current_process;
 
    current_process = get_process( id );
    current_process->runnable = false;
    return 0;
}


int xthread_resume( processID id )
{
    process *current_process;
 
    current_process = get_process( id );
    current_process->runnable = true;
    return 0;
}


int xthread_mutex_init( xthread_mutex_t *mutex )
{
    int i = 0;
  
    mutex->locked = false;
    for( i = 0; i < MAX_THREADS; i++ ) {
        mutex->waiting[i] = false;
    }
    mutex->waiting_index = 0;
  
    return 0;
}


int xthread_mutex_lock( xthread_mutex_t *mutex, processID proc )
{
    int return_value = 1;
    
    disable_interrupts( );
    if( mutex->locked == false ) {
        mutex->locked = true;
        mutex->waiting[proc.pid] = false;
        enable_interrupts( );
	
        debug_print( lock_counter++, 39, "u", COLOR );
	
        return_value = 0;
    }
    else {
        xthread_suspend( proc );
        mutex->waiting[proc.pid] = true;
	
        debug_print( lock_counter++, 39, "l", COLOR );
    
        enable_interrupts( );
        xthread_switch_thread( );
        return_value = xthread_mutex_lock( mutex, proc );
    }
    return return_value;
}


int xthread_mutex_unlock( xthread_mutex_t *mutex )
{
    processID proc;
    int counter = 0;
  
    while( mutex->waiting[mutex->waiting_index] != true && counter < MAX_THREADS ) {
        mutex->waiting_index++;
        counter++;
    
        if( mutex->waiting_index == MAX_THREADS ) {
            mutex->waiting_index = 0;
        }
    }
  
    mutex->locked = false;
    if( counter != MAX_THREADS ) {
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
