/****************************************************************************
FILE          : types.h
LAST REVISION : 2008-02-14
SUBJECT       : Definition of common types.
PROGRAMMER    : (C) Copyright 2008 by The Phoenix Team.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#ifndef TYPES_H
#define TYPES_H

/*! \file types.h Useful type definitions.
 *
 * This file contains various type definitions that are useful across the Phoenix project.
 * Rather than defining these types in multiple places and running the risk of the definitions
 * becoming inconsistent, modules should include this header instead.
 */

typedef unsigned char  byte;  //!< Use for raw 8 bit values.
typedef unsigned short word;  //!< Use for raw 16 bit values.

typedef enum { OK = 0x00, BAD_ARGS = 0x01, NOT_IMPL = 0x02 } video_error_t;

typedef enum {
    DEFAULT,
    PRINT_AT,
    SET_MODE,
    CLEAR_SCREEN,
    VGA_PRINT_AT, 
    PUT_PIXEL,
    GET_PIXEL,
    LINE,
    POLYGON,
    RECT,
    RECT_FILL,
    CIRCLE, 
    FILL,
    BOUNDARY_FILL,
    PUT_IMAGE,
    PUT_TRANS_IMAGE
} video_func_t;

typedef enum { K_DEFAULT, GETKEY, GETNEWKEYS, GETKEYSTRING } keyboard_func_t;

#ifndef __cplusplus
//! Use for true/false flags, etc.
typedef enum { false = 0, true = 1 } bool;
#endif

#endif

