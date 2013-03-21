/****************************************************************************
FILE          : xbuffer.h
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix buffers.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This header file specifies the interface to Phoenix buffers.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xthread.h"
#include "message.h"

#ifndef XBUFFER_H
#define XBUFFER_H

#define XBUFFER_SIZE 8

// This is our semaphore type.
typedef struct {
    xthread_mutex_t lock;
    xthread_cond_t  non_zero;
    int             raw_count;
} semaphore;

void semaphore_init(semaphore *, int);
void semaphore_destroy(semaphore *);
void semaphore_up(semaphore *, processID);
void semaphore_down(semaphore *, processID);

// This is our producer/consumer buffer type.
typedef struct {
    message *buffer[XBUFFER_SIZE];
    xthread_mutex_t lock;
    semaphore       used;      // Use our semaphores here.
    semaphore       free;      // ...
} xbuffer;

void  xbuffer_init(xbuffer *);
void  xbuffer_destroy(xbuffer *, processID);
void  xbuffer_push(xbuffer *, message *, processID);
message *xbuffer_pop(xbuffer *, processID *, processID *);

#endif

