/****************************************************************************
FILE          : superMtx.c
LAST REVISION : 2008-03-06
SUBJECT       : Tests thread creation and context switching.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This test will exercise the mutexes by quickly locking and unlocking in two threads. This
functionality is basic to the thread support and must work correctly before the message passing
system will work.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/
#include "xthread.h"
#include "xtimer.h"
#include "video.h"
#include "xstddef.h"
#include "message.h"
#include "xbuffer.h"
#include "xstring.h"

#define TRACE_COLUMN 60
#define OUTPUT_COLUMN 10
#define COLOR 0x04

int trace_counter = 0;
int output_counter = 0;
processID id1;
processID id2;

int mutex_state = 0;

xthread_mutex_t mutex;

// Thread functions.
void *thread1(void);
void *thread2(void);

int main()
{  
    id1.pid = 0;
    id2.pid = 1;
	
    clear_screen();
    print_at(trace_counter++, TRACE_COLUMN, "Start of main", COLOR);
  
    _asm {
        CLI
    };
  
    initialize_timer_frequency();
    initialize_timerISR();
    print_at(trace_counter++, TRACE_COLUMN, "Timer initialized", COLOR);
 
    xthread_mutex_init(&mutex);
    print_at(trace_counter++, TRACE_COLUMN, "Mutex initialized", COLOR);
 
    if (xthread_create(id1, thread1)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create thread 1", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created thread 1", COLOR);
    }
  
    if (xthread_create(id2, thread2)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create thread 2", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created thread 2", COLOR);
    }
 
    _asm {
        STI
    };
  
    print_at(trace_counter++, TRACE_COLUMN, "Looping in main", COLOR);
    for (;;) { }
    print_at(trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR);
    return 0;
}


// Thread 1
void *thread1(void)
{
    while(1) {
        xthread_mutex_lock(&mutex, id1);
        if(mutex_state != 0) {
            print_at(0, TRACE_COLUMN, "BAD THINGS!!!", COLOR);
        }
	
        mutex_state = 1;
        print_at(trace_counter++, 0, "Thread1 got lock", COLOR);
        mutex_state = 0;
	
        xthread_mutex_unlock(&mutex);
    }
    return NULL;
}


// Thread 2
void *thread2(void)
{
    while (1) {
        xthread_mutex_lock(&mutex, id2);
        if (mutex_state != 0) {
            print_at(0, TRACE_COLUMN, "BAD THINGS!!!", COLOR);
        }
	
        mutex_state = 2;
        print_at(trace_counter++, 18, "Thread2 got lock", COLOR);
        mutex_state = 0;
	
        xthread_mutex_unlock(&mutex);
    }
    return NULL;
}

