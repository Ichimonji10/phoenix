/****************************************************************************
FILE          : xstddef.h
LAST REVISION : 2008-02-14
SUBJECT       : Standard defines for Phoenix
PROGRAMMER    : (C) Copyright 2008 by The Phoenix Team.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#ifndef XSTDDEF_H
#define XSTDDEF_H

/*! \file xstddef.h Various standard definitions.

    This file contains useful macros and other definitions that are needed in
    many other files. This file is intended to mimic the standard header
    stddef.h.
 */

#define NULL ((void*)0)  //!< A pointer that doesn't point at anything.
#define sgn(x) ((x<0)?-1:((x>0)?1:0))  //!< A macro to return the sign of a number
#define abs(a) (((a)<0)?-(a):(a))  //!< A macro to return the absolute value of a number.

#define MAX_THREADS 16    //!< Maximum number of threads in the OS.

#define IDLE 0           //!< Process ID of the main thread.
#define VIDEO 1          //!< Process ID of the video module.
#define KEYBOARD 2              //!< Process ID of the keyboard module.
#define MAIN  MAX_THREADS - 2   //!< Process ID of the main thread.  Should be MAX_THREADS - 1

#endif

