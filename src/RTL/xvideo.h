/****************************************************************************
FILE          : xvideo.h
LAST REVISION : 2008-04-22
SUBJECT       : Interface to video system using Phoenix message passing.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

Interface to video system using Phoenix message passing.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "types.h"

#ifndef XVIDEO_H
#define XVIDEO_H

void xvideo_put_pixel(int x, int y, byte color);
void xvideo_line(int x1, int y1, int x2, int y2, byte color);
void xvideo_circle(int x1, int y1, int radius, byte color);
void xvideo_print_at(int row, int col, char *string, byte color);
void xvideo_vga_print_at(int row, int col, char *string, byte color);

void xvideo_clear_screen();
void xvideo_set_mode();
void xvideo_put_image(int x, int y, const char *name);
void xvideo_put_trans_image(int x, int y, byte color, const char *name);
void xvideo_rect_fill(int left, int top, int right, int bottom, byte color);
byte xvideo_get_pixel(int x, int y);

#endif

