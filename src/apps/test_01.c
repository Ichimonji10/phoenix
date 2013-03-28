/****************************************************************************
FILE          : test_01.c
LAST REVISION : 2008-02-29
SUBJECT       : Tests message passing to the video module.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This basic test will test message passing functionality by remotely using the video module.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xtimer.h"
#include "message.h"
#include "vga.h"
#include "video.h"
#include "xstddef.h"
#include "xstring.h"
#include "vparser.h"
#include "debug.h"
#include "xvideo.h"

#define TRACE_COLUMN 60
#define COLOR 0x04

int trace_counter = 0;

processID vidid;
processID testid;
processID hackid;

void *test( void );
void *hack( void );

int main( void )
{
    vidid.pid  = VIDEO;
    testid.pid = MAIN;
    hackid.pid = 3;
	
    clear_screen( );
  
    disable_interrupts( );
  
    initialize_timer_frequency( );
    initialize_timerISR( );
    print_at( trace_counter++, TRACE_COLUMN, "Timer initialized", COLOR );
  
    message_init();
    print_at( trace_counter++, TRACE_COLUMN, "Messages initialized", COLOR );
 
    if( xthread_create( vidid, run_video ) ) {
        print_at( trace_counter++, TRACE_COLUMN, "Failed to create video thread", COLOR );
    }
    else {
        print_at( trace_counter++, TRACE_COLUMN, "Created video thread", COLOR );
    }
  
    if( xthread_create( testid, test ) ) {
        print_at( trace_counter++, TRACE_COLUMN, "Failed to create test thread", COLOR );
    }
    else {
        print_at( trace_counter++, TRACE_COLUMN, "Created test thread", COLOR );
    }
  
  
    if( xthread_create( hackid, hack ) ) {
        print_at( trace_counter++, TRACE_COLUMN, "Failed to create hack thread", COLOR );
    }
    else {
        print_at( trace_counter++, TRACE_COLUMN, "Created hack thread", COLOR );
    } 
 
    enable_interrupts( );
  
    print_at( trace_counter++, TRACE_COLUMN, "Looping in main", COLOR );
    for ( ;; ) { }
    print_at( trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR );
    return 0;
}


void *test( void )
{
    int row = 0;
    int i, j;
    byte color = 0x01;
  
    while( 1 ) {
        if( row < 0 ) {
            row = 0;
        }
  
        xvideo_print_at( row, 1, "Phoenix Lives!!", color );
        row++;
        color++;
    
        //Delay
        for( i = 0; i < 1000; i++ ) {
            for( j = 0; j < 2000; j++ ) { }
        }
    }
    return NULL;
}


void *hack( void )
{
    while( 1 ) { }
    return NULL;
}

