/****************************************************************************
FILE          : kparser.c
LAST REVISION : 2008-03-25
SUBJECT       : Message parser for the keyboard system
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

Message parser for the video system

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "keyboard.h"
#include "message.h"
#include "types.h"
#include "debug.h"
#include "xstring.h"

void *run_keyboard( void )
{
    message      received;
    char         rec_buff[5120];
    message      response;
    keyboard_func_t func = DEFAULT;
    processID    self;
    char         *current;
    char         c;
  
    // set own pid to globally defined VIDEO pid
    self.pid = KEYBOARD;
  
    // setup the structure for received messages
    received.data = &rec_buff;
    received.dest = self;
  
    // set the response source to us
    response.src = self;
    response.size = 0;
  
    while( 1 ) {
        //try to get a message, waits until one's available 
        message_receive( &received );
	
        debug_print( debug_counter++, 33, "KRCV", 0x05 );
        if( received.src.pid != -1 ) {
    
            // point to the beginning of incoming data 
            current = received.data;

            // extract the function name
            func = get_int( current );
	
            current += 2;
    
            // attempt to run the named function
            switch( func ) {
            case GETKEY:
                c = getKey( );
                response.data = &c;
                break;
                
            case GETNEWKEYS:
                response.data = getNewkeys( );
                response.size = xstrlen( getNewkeys( ) );
                break;
                
            case GETKEYSTRING:
                response.data = getNewkeys( );
                break;
                
            default:
                debug_print( debug_counter++, 24, "DFT", 0x05 );
                debug_print( debug_counter++, 1, current-2, 0x04 );
                break;
            }
    
            response.size = 2;
    
            response.dest = received.src;
            debug_print( debug_counter++, 24, "RPY", 0x05 );
            message_reply( &response );
        }
    }
    return NULL;
}

