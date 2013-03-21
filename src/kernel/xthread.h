/****************************************************************************
FILE          : xthread.h
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix threading.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This header file describes the Phoenix threading system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/


#ifndef XTHREAD_H
#define XTHREAD_H

#include "xstddef.h"
#include "types.h"

#define STACK_SIZE 512  // In words

// Make sure all members of the following structures are byte aligned.
// These structures are accessed from assembly language in xt_asm.asm
// and that code depends on these structurs being layed out a certain way.
//
#pragma pack(push, 1);
typedef struct {
    int pid;
} processID;

typedef struct {
    word      far* stack;
    bool      runnable;
    processID pid;
} process;

typedef struct {
    bool locked;  // false if available, true if locked
    bool waiting[MAX_THREADS];
    int  waiting_index;
}xthread_mutex_t;

typedef struct {
    bool waiting[MAX_THREADS];
    int  waiting_index;
}xthread_cond_t;

#pragma pack(pop);
// End of structures with specific alignment requirements.

int xthread_create(processID id, void (*start_routine));
int xthread_suspend(processID id);
int xthread_resume(processID id);
int xthread_mutex_init(xthread_mutex_t *);
int xthread_mutex_lock(xthread_mutex_t *, processID);
int xthread_mutex_unlock(xthread_mutex_t *);
int xthread_cond_init(xthread_cond_t *);
int xthread_cond_wait(xthread_cond_t *, xthread_mutex_t *, processID);
int xthread_cond_signal(xthread_cond_t *);
void xthread_switch_thread();
void disable_interrupts();
void enable_interrupts();

#endif

