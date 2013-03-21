/****************************************************************************
FILE          : message.c
LAST REVISION : 2008-01-22
SUBJECT       : Interface to Phoenix message passing.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This file defines the interface to the Phoenix message passing system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "types.h"
#include "xstring.h"
#include "message.h"

void xvideo_put_pixel(int x, int y, byte color)
{
    message request;
    message result;
    char request_buff[32];
    char result_buff;
    char *temp = &request_buff;
    int size = 0;
    video_func_t function;
   
    function = PUT_PIXEL;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x, temp);
    size += 2;
   
    // load y
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y, temp);
    size += 2;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &request_buff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}


void xvideo_line(int x1, int y1, int x2, int y2, byte color)
{
    message request;
    message result;
    char request_buff[32];
    char result_buff;
    char *temp = &request_buff;
    int size = 0;
    video_func_t function;
   
    function = LINE;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x1
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x1, temp);
    size += 2;
   
    // load y1
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y1, temp);
    size += 2;
   
    // load x2
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x2, temp);
    size += 2;
   
    // load y2
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y2, temp);
    size += 2;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &request_buff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}


void xvideo_circle(int x, int y, int radius, byte color)
{
    message request;
    message result;
    char request_buff[32];
    char result_buff;
    char *temp = &request_buff;
    int size = 0;
    video_func_t function;
   
    function = CIRCLE;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x, temp);
    size += 2;
   
    // load y
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y, temp);
    size += 2;
   
    // load radius
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(radius, temp);
    size += 2;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &request_buff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    message_send(&request, &result);//throw(&testVideo);
}


void xvideo_print_at(int row, int col, char *string, byte color)
{  
    message request;
    message result;
    char testBuff[128];
    char result_buff;
    char *temp = &testBuff;
    int size = 0;
    video_func_t function;
   
    function = PRINT_AT;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load row of row
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(row, temp);
    size += 2;
   
    // load column of col
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(col, temp);
    size += 2;
   
    // load message
    temp = add_int_to_message(xstrlen(string)+1, temp);
    size += 2;
    xstrcpy(temp, string);
    temp += xstrlen(string)+1;
    size += xstrlen(string)+1;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &testBuff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}


void xvideo_vga_print_at(int row, int col, char *string, byte color)
{  
    message request;
    message result;
    char testBuff[128];
    char result_buff;
    char *temp = &testBuff;
    int size = 0;
    video_func_t function;
   
    function = VGA_PRINT_AT;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load row of row
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(row, temp);
    size += 2;
   
    // load column of col
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(col, temp);
    size += 2;
   
    // load message
    temp = add_int_to_message(xstrlen(string)+1, temp);
    size += 2;
    xstrcpy(temp, string);
    temp += xstrlen(string)+1;
    size += xstrlen(string)+1;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &testBuff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    message_send(&request, &result);//throw(&request);
}


void xvideo_rect_fill(int left, int top, int right, int bottom, byte color)
{
    message request;
    message result;
    char request_buff[32];
    char result_buff;
    char *temp = &request_buff;
    int size = 0;
    video_func_t function;
   
    function = RECT_FILL;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load left
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(left, temp);
    size += 2;
   
    // load top
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(top, temp);
    size += 2;
   
    // load right
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(right, temp);
    size += 2;
   
    // load bottom
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(bottom, temp);
    size += 2;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &request_buff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}


byte xvideo_get_pixel(int x, int y)
{
    message request;
    message result;
    char request_buff[32];
    char result_buff;
    char *temp = &request_buff;
    int size = 0;
    video_func_t function;
   
    function = GET_PIXEL;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x, temp);
    size += 2;
   
    // load y
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y, temp);
    size += 2;
   
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &request_buff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    message_receive(&result);
   
    return *result.data;
}


void xvideo_clear_screen();
void xvideo_set_mode();

void xvideo_put_image(int x, int y, const char *name)
{
    message request;
    message result;
    char testBuff[128];
    char result_buff;
    char *temp = &testBuff;
    int size = 0;
    video_func_t function;
   
    function = PUT_IMAGE;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x, temp);
    size += 2;
   
    // load y
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y, temp);
    size += 2;
   
    // load message
    temp = add_int_to_message(xstrlen(name)+1, temp);
    size += 2;
    xstrcpy(temp, name);
    temp += xstrlen(name)+1;
    size += xstrlen(name)+1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &testBuff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}


void xvideo_put_trans_image(int x, int y, byte color, const char *name)
{
    message request;
    message result;
    char testBuff[128];
    char result_buff;
    char *temp = &testBuff;
    int size = 0;
    video_func_t function;
   
    function = PUT_TRANS_IMAGE;
   
    // load function name
    // cast as int to use a fixed width
    temp = add_int_to_message(function, temp);
    size += 2;
   
    // load x
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(x, temp);
    size += 2;
   
    // load y
    temp = add_int_to_message(2, temp);
    size += 2;
    temp = add_int_to_message(y, temp);
    size += 2;
   
    // load color
    temp = add_int_to_message(1, temp);
    size += 2;
    *temp = color;
    temp += 1;
    size += 1;
   
    // load message
    temp = add_int_to_message(xstrlen(name)+1, temp);
    size += 2;
    xstrcpy(temp, name);
    temp += xstrlen(name)+1;
    size += xstrlen(name)+1;
 
    request.src.pid = MAIN;
    request.dest.pid = VIDEO;
    request.size = size;
    request.data = &testBuff;
   
    result.data = &result_buff;
    result.src.pid = VIDEO;
    result.dest.pid = MAIN;
   
    //message_send(&request, &result);
    message_throw(&request);
    xthread_switch_thread();
}

