/****************************************************************************
FILE          : message.h
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix message passing.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This header file specifies the interface to the Phoenix message passing system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xthread.h"
#include "xtimer.h"

#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct {
    processID src;    //!< Thread ID where this message was created
    processID dest;   //!< Thread ID where this message is being sent
    int size;         //!< Number of bytes in message data
    char *data;       //!< Pointer to the message itself
} message;

void message_send( message *request, message *response );
void message_throw( message *request );
void message_receive( message *request );
void message_reply( message *response );
int  message_init( );
int  get_int( char *current);
char *add_int_to_message( int value, char *buff );

#endif

