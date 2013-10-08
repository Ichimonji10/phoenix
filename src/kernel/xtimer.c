/****************************************************************************
FILE          : xtimer.c
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix message passing.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This file defines the interface to the Phoenix message passing system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Williston, VT 05495
    PChapin@vtc.vsc.edu
****************************************************************************/

#include <i86.h>

#include "xtimer.h"
#include "xthread.h"
#include "xrndbuff.h"
#include "video.h"
#include "xstddef.h"
#include "debug.h"

/*! \file xtimer.c Timer handling functions.
 *
 * When you figure out what these functions do, document them here.
 */

// The following functions are written in assembly language.
extern void create_process_asm( void *(*start_routine)( void ), word *stack );
extern void __interrupt Timer_ISR_asm( void );

void *idle_thread( void );

static void (__interrupt * __far * __far IVT)( void );

static unsigned int count = 10;
static int col = 8;
unsigned int sch_count = 0;
// static unsigned long deadbeef_seed = 0;
// static unsigned long deadbeef_beef = 0xdeadbeef;
static bool first_time = true;

// Timer interrupt function.
word far *Schedule( word far *p )
{
    process * current = get_current( );
    process * candidate;
    processID idle;
    int i;

    if( NULL == current ) {
        print_at( count++, col, "thread pointing to NULL", 0x04 );
        print_at( count++, col, "(did you call add_process()?)", 0x04 );
        return p;
    }

    if( first_time ) {
        first_time = false;
        candidate = get_next( );
        return candidate->stack;
    }

    candidate = get_next( );
    while( candidate->pid.pid != current->pid.pid ) {
        if( true == candidate->runnable ) {
            return candidate->stack;
        }
    }

    // no suitable candidate found. Run idle
    idle.pid = IDLE;
    candidate = get_process( idle );
    set_idle( ); // update "current" index. Make get_process do this automatic
    return candidate->stack;
}


void *idle_thread( void )
{
    enable_interrupts( );
    while( 1 ) { }
    return NULL;
}


// Create idle thread.
void create_idle_thread( void )
{
    processID idleid;
    idleid.pid = IDLE;
    xthread_create( idleid, idle_thread );
    return;
}


// Initialize the timer interrupt.
void initialize_timerISR( void )
{
    create_idle_thread( );  // Be sure the thread exists before we activate context switching.
    IVT = MK_FP( 0, 0 );
    IVT[TimerIRQ] = Timer_ISR_asm;
}


// Initialize_timer_frequency to ~2.8ms.
void initialize_timer_frequency( void )
{
    outp( 0x42, 0x3c );
    outp( 0x40, 0x00 );
    outp( 0x40, 0x10 );
}


//reset the interrupt vector back to normal
/*void reset_timer_interrupt( void )
{
  _dos_setvect( TimerIRQ, Old_TimerISR );
  outp( 0x43, 0x3c );
  outp( 0x40, LOW_BYTE(0xFFFF) );
  outp( 0x40, HIGH_BYTE(0xFFFF) );
}
*/

// based on Robert Haarman's deadbeef prng
// http://inglorion.net/software/deadbeef_rand/
unsigned int get_random( void )
{
/*
    if( deadbeef_seed == 0 ) {
        deadbeef_seed  = random_seed( );
        deadbeef_seed *= random_seed( );
        deadbeef_seed *= random_seed( );
    }

    deadbeef_seed = (deadbeef_seed << 7) ^ ((deadbeef_seed >> 25) + deadbeef_beef);
    deadbeef_beef = (deadbeef_beef << 7) ^ ((deadbeef_beef >> 25) + 0xdeadbeef);

    return (unsigned int)deadbeef_seed;
*/
    return 0;
}


int random_seed( )
{
    return (int)inp( 0x40 );
}
