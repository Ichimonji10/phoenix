/****************************************************************************
FILE          : testMtx.c
LAST REVISION : 2008-03-06
SUBJECT       : Tests basic mutex usage.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This test will exercise the mutexes and condition variables. This functionality is basic to the
thread support and must work correctly before the message passing system will work.

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

#define TRACE_COLUMN 20
#define OUTPUT_COLUMN 10
#define COLOR 0x04

int trace_counter = 0;
processID id1;
processID id2;

xbuffer message_buffer;

// Thread functions.
void *thread1( void );
void *thread2( void );

int main( void )
{  
    id1.pid = 0;
    id2.pid = 1;
	
    clear_screen( );
    print_at( trace_counter++, TRACE_COLUMN, "Start of main", COLOR );
  
    _asm {
        CLI
    };
  
    initialize_timer_frequency( );
    initialize_timerISR( );
    print_at( trace_counter++, TRACE_COLUMN, "Timer initialized", COLOR );
  
    xbuffer_init( &message_buffer );
    print_at( trace_counter++, TRACE_COLUMN, "Initialized xbuffer", COLOR ); 
 
    if( xthread_create( id1, thread1 ) ) {
        print_at( trace_counter++, TRACE_COLUMN, "Failed to create thread 1", COLOR );
    }
    else {
        print_at( trace_counter++, TRACE_COLUMN, "Created thread 1", COLOR );
    }
  
    if( xthread_create( id2, thread2 ) ) {
        print_at( trace_counter++, TRACE_COLUMN, "Failed to create thread 2", COLOR );
    }
    else {
        print_at( trace_counter++, TRACE_COLUMN, "Created thread 2", COLOR );
    }
 
    _asm {
        STI
    };
  
    print_at( trace_counter++, TRACE_COLUMN, "Looping in main", COLOR );
    for( ;; ) { }
    print_at( trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR );
    return 0;
}


// Thread 1
void *thread1( void )
{
    message  send;
    message *receive;
    char     buffer[32];

    send.src  = id1;
    send.dest = id2;
  
    xstrcpy( &buffer, "XBuffer push and pop" );
    send.data = &buffer;
    send.size = 21;
  
    xbuffer_push( &message_buffer, &send, id1 );
  
    print_at( trace_counter++, TRACE_COLUMN, "Buffer pushed", COLOR );
  
    xthread_suspend( id1 );
    xthread_switch_thread( );
  
    receive = xbuffer_pop( &message_buffer, &id2, &id1 );
    print_at( trace_counter++, TRACE_COLUMN, "Buffer popped", COLOR );
    print_at( trace_counter++, TRACE_COLUMN, receive->data, COLOR );
    print_at( trace_counter++, TRACE_COLUMN, "Eternal Loopiness", COLOR );
  
    while( 1 ) { }
    return NULL;
}


// Thread 2
void *thread2( void )
{
    message  send;
    message *receive;
    char     buffer[32];

    send.src  = id2;
    send.dest = id1;
  
    receive = xbuffer_pop( &message_buffer, &id1, &id2 );
    print_at( trace_counter++, TRACE_COLUMN, "Buffer popped", COLOR );
    print_at( trace_counter++, TRACE_COLUMN, receive->data, COLOR );
  
    xstrcpy( &buffer, "appears to be working" );
    send.data = &buffer;
    send.size = 22;
  
    xbuffer_push( &message_buffer, &send, id2 );
    print_at( trace_counter++, TRACE_COLUMN, "Buffer pushed", COLOR );
    xthread_suspend( id2 );
    xthread_resume( id1 );
    xthread_switch_thread( );
    return NULL;
}

