/****************************************************************************
FILE          : test_01.c
LAST REVISION : 2008-03-27
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
#include "kparser.h"

#define TRACE_COLUMN 60
#define COLOR 0x04

int trace_counter = 0;
unsigned int row = 0;
processID keyboardid;
processID testid;
processID hackid;

void *test(void);
void *hack(void);

int main(void)
{
    keyboardid.pid = KEYBOARD;
    testid.pid = MAIN;
    hackid.pid = 3;
	
    clear_screen();
  
    _asm {
        CLI
    };
  
    initialize_timer_frequency();
    initialize_timerISR();
    print_at(trace_counter++, TRACE_COLUMN, "Timer initialized", COLOR);
  
    message_init();
    print_at(trace_counter++, TRACE_COLUMN, "Messages initialized", COLOR);

    if (xthread_create(keyboardid, run_keyboard)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create keyboard thread", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created keyboard thread", COLOR);
    }
  
    if (xthread_create(testid, test)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create test thread", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created test thread", COLOR);
    }

    if (xthread_create(hackid, hack)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create hack thread", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created hack thread", COLOR);
    }

    _asm {
        STI
    };
  
    print_at(trace_counter++, TRACE_COLUMN, "Looping in main", COLOR);
    for (;;) { }
    print_at(trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR);
    return 0;
}


void keyboard_test_message()
{  
    message testKeyboard;
    message result;
    char testBuff[128];
    char *temp = testBuff;
    int size = 0;
    keyboard_func_t function;
   
    function = GETNEWKEYS;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
    
    testKeyboard.src.pid = MAIN;
    testKeyboard.dest.pid = KEYBOARD;
    testKeyboard.size = size;
    testKeyboard.data = &testBuff;
   
    result.src.pid = KEYBOARD;
    result.dest.pid = MAIN;
   
    message_send(&testKeyboard, &result);
   
    if (result.data) {
        print_at(row++, 1, result.data, 0x04);
    }
    else {
        print_at(row++, 2, "NULL", 0x02);
    }
}


void *test(void)
{
    while (1) {
        keyboard_test_message();
    }
    return NULL;
}


void *hack(void)
{
    int row = 0;

    while (1) {
        print_at(row, 0, "1", 0x05);
        row++;
    }
    return NULL;
}

