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
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xtimer.h"
#include "xthread.h"
#include "xrndbuff.h"
#include "video.h"
#include "xstddef.h"
#include <i86.h>
#include "debug.h"

/*! \file xtimer.c Timer handling functions.

    When you figure out what these functions do, document them here.
 */

extern void create_process_asm(void (*start_routine)(void), word *stack);
extern void store_process_asm(word *stack);
extern void next_process_asm(word *stack);
extern void switch_process_asm(word *stack);
extern void __interrupt Timer_ISR_asm(void);

void *idle_thread(void);

static void (__interrupt * __far * __far IVT)(void);

static unsigned int count = 10;
static int col = 8;
unsigned int sch_count = 0;
//static unsigned long deadbeef_seed = 0;
//static unsigned long deadbeef_beef = 0xdeadbeef;
static bool first_time = true;

//timer interrupt function
word far* Timer_ISR(word far* p)
{
    processID idle;
    process *current_process;
    process *next_process;

    idle.pid = IDLE;

    if (first_time) {
        current_process = getNext();
        setCurrent();
        first_time = false;
        return current_process->stack;
    }

    current_process = getCurrent();

    if (current_process == NULL) {
        print_at(count++, col, "thread pointing to NULL", 0x04);
        return p;
    }

    current_process->stack = p;

    next_process = getNext();

    //search for next runnable thread
    while (next_process->runnable == false || next_process->pid.pid == IDLE) {
        debug_print(sch_count++, 46, "SCH", 0x03);
        //run idle thread if it loop around the xroundbuffer and no runnable thread
        if (next_process->pid.pid == current_process->pid.pid) {
            next_process = getProcess(idle);

            setIdle();
            debug_print(sch_count++, 46, "IDL", 0x03);
            return next_process->stack;
        }
        next_process = getNext();
    }

    if (next_process->pid.pid == current_process->pid.pid) {
        setCurrent();
        return p; //return to asm
    }

    setCurrent();
    return next_process->stack;
}


void *idle_thread(void)
{
    enable_interrupts();
    while(1) { }
    return NULL;
}


//create idel thread
void create_idle_thread()
{
    processID idleid;
    idleid.pid = IDLE;
    xthread_create(idleid, idle_thread);
    return;
}


//initialize the timer interrupt
void initialize_timerISR()
{
    IVT = MK_FP(0,0);
    IVT[TimerIRQ] = Timer_ISR_asm;
    create_idle_thread();
}


//initialize_timer_frequency to ~2.8ms
void initialize_timer_frequency()
{
    outp(0x42, 0x3c);
    outp(0x40, 0x00);
    outp(0x40, 0x10);
}


//reset the interrupt vector back to normal
/*void reset_timer_interrupt()
{
  _dos_setvect(TimerIRQ, Old_TimerISR);
  outp(0x43, 0x3c);
  outp(0x40, LOW_BYTE(0xFFFF));
  outp(0x40, HIGH_BYTE(0xFFFF));
}
*/

// based on Robert Haarman's deadbeef prng
// http://inglorion.net/software/deadbeef_rand/
unsigned int get_random()
{
/*
    if (deadbeef_seed == 0) {
        deadbeef_seed = random_seed();
        deadbeef_seed *= random_seed();
        deadbeef_seed *= random_seed();
    }

    deadbeef_seed = (deadbeef_seed << 7) ^ ((deadbeef_seed >> 25) + deadbeef_beef);
    deadbeef_beef = (deadbeef_beef << 7) ^ ((deadbeef_beef >> 25) + 0xdeadbeef);

    return (unsigned int)deadbeef_seed;
*/
    return 0;
}


int random_seed()
{
    return (int)inp(0x40);
}

