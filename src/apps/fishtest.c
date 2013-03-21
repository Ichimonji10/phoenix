/****************************************************************************
FILE          : fishtest.c
LAST REVISION : 2008-03-27
SUBJECT       : Tests displaying an image.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This basic test will test displaying an image using the message passing system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xtimer.h"
#include "video.h"
#include "vga.h"
#include "message.h"
#include "xstddef.h"
#include "vparser.h"
#include "xstring.h"

#define TRACE_COLUMN 60
#define COLOR 0x04

int trace_counter = 0;

processID vidid;
processID testid;
processID hackid;

void *test(void);
void *hack(void);

int main(void)
{
    vidid.pid = VIDEO;
    testid.pid = MAIN;
    hackid.pid = 3;
  
    set_mode(VGA_MODE);
  
    disable_interrupts();
  
    initialize_timer_frequency();
    initialize_timerISR();
    print_at(trace_counter++, TRACE_COLUMN, "Timer initialized", COLOR);
  
    message_init();
    print_at(trace_counter++, TRACE_COLUMN, "Messages initialized", COLOR);
 
    if (xthread_create(vidid, run_video)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create video thread", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created video thread", COLOR);
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
    enable_interrupts();
  
    put_image(10, 10, "rocket");

    print_at(trace_counter++, TRACE_COLUMN, "Looping in main", COLOR);
    for (;;){ }
    print_at(trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR);
    return 0;
}


void mode13()
{
    set_mode(VGA_MODE);
    put_pixel(100, 101, 4);
    line(40, 40, 100, 60, 6);
    rect(140, 50, 230, 80, 4);
}


void fish_test()
{  
    message testVideo;
    message result;
    char testBuff[128];
    char *temp = &testBuff;
    int size = 0;
    video_func_t function;
   
    function = PUT_IMAGE;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(0, temp);
    size += 2;
   
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(0, temp);
    size += 2;
   
    // load message
    temp = add_int_to_message(xstrlen("rocket"), temp);
    size += 2;
    xstrcpy(temp, "rocket");
    temp += xstrlen("rocket");
    size += xstrlen("rocket");
 
    testVideo.src.pid = MAIN;
    testVideo.dest.pid = VIDEO;
    testVideo.size = size;
    testVideo.data = &testBuff;
   
    message_send(&testVideo, &result);
}


void *test(void)
{
    put_image(100, 10, "rocket");
    fish_test();
    return NULL;
}


void *hack(void)
{
    while(1) { }
    return NULL;
}

