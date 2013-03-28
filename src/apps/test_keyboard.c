/****************************************************************************
FILE          : test_keyboard.c
LAST REVISION : 2008-03-27
SUBJECT       : Tests message passing to the video module.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/
#include "video.h"
#include "keyboard.h"
#include "types.h"
#include "xkeyboard.h"

int col_counter = 0;
int row = 0;

int main( void )
{ 
    char c[2];
    c[1] = '\0';
  
    initialize_keyboardISR( );
    clear_screen( );
    print_at( row++, 0, "initialized keyboard interrupt", 0x04 );
  
    print_at( row++, 0, "Looping in Main", 0x04 );
    while( 1 ) {
        if( hasRead( ) ) {
            c[0] = xkeyboard_getKey( );
            print_at( 3, col_counter++, c, 0x03 );
            finishRead( );
        }
    }
    return 0;
}

/*key code 224 means arrow key.
Arrow up key press: 72, 200, 170, 42 are the return key codes
Arrow left key press: 75, 203, 170, 42 are the return key codes
Arrow down key press: 80, 208, 170, 42 are the return key codes
Arrow right key press: 77, 224, 170, 42 are the return key codes
*/

