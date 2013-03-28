/****************************************************************************
FILE          : beepTest.c
LAST REVISION : 2008-04-18
SUBJECT       : Test the beep function
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This is program to test the audio system

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "beep.h"

int main( void )
{ 
    while( 1 ) {
        beep(  C5 );
        beep( A4S );
        beep(  F4 );
        beep(  C5 );
        beep( A4S );
        beep(  F4 );
        beep(  C5 );
        beep( A4S );
        beep(  F4 );
        beep(  C5 );
        beep( A4S );
        beep(  F4 );
        beep(  C5 );
        beep(  C5 );
        beep(  C5 );
    }
    return 0;
}

