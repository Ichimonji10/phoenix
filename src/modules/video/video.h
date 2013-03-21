/****************************************************************************
FILE          : video.h
LAST REVISION : 2008-04-16
SUBJECT       : Interface for Phoenix video.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This header file describes the Phoenix video system.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/
#include "types.h"

#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define GET_MODE            0x0F      /* BIOD func to get the video mode/ */

// Prints a character string to a specific location with color information (used in mode 0x03);
void print_at(int row, int column, const char *message, byte color);

// Sets the video mode
// 13h
void set_mode(byte mode);

// Crears the screen
void clear_screen();

#endif


