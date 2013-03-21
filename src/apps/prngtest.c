/****************************************************************************
FILE          : prngtest.c
LAST REVISION : 2008-03-27
SUBJECT       : Tests the prng.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

This basic test will test the prng.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xtimer.h"
#include "stdio.h"

int main(void)
{
    double bits[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int i = 0;
    int random = 0;
  
    for (i = 0; i < 30000; i++) {
        random = get_random();
	
        if ((random&0x01) == 1) {
            bits[0]++;
        }
    
        if (((random >> 1)&0x01) == 1)  {
            bits[1]++;
        }
	
        if (((random >> 2)&0x01) == 1) {
            bits[2]++;
        }
	
        if (((random >> 3)&0x01) == 1) {
            bits[3]++;
        }
	
        if (((random >> 4)&0x01) == 1)  {
            bits[4]++;
        }
	
        if (((random >> 5)&0x01) == 1)  {
            bits[5]++;
        }
	
        if (((random >> 6)&0x01) == 1)  {
            bits[6]++;
        }
	
        if (((random >> 7)&0x01) == 1)  {
            bits[7]++;
        }
	
        if (((random >> 8)&0x01) == 1) {
            bits[8]++;
        }
	
        if (((random >> 9)&0x01) == 1) {
            bits[9]++;
        }
	
        if (((random >> 10)&0x01) == 1) {
            bits[10]++;
        }
	
        if (((random >> 11)&0x01) == 1) {
            bits[11]++;
        }
	
        if (((random >> 12)&0x01) == 1) {
            bits[12]++;
        }
	
        if (((random >> 13)&0x01) == 1) {
            bits[13]++;
        }
	
        if (((random >> 14)&0x01) == 1) {
            bits[14]++;
        }
	
        if (((random >> 15)&0x01) == 1) {
            bits[15]++;
        }
    }
  
    for (i = 0; i < 16; i++) {
        printf("%f\n", bits[i]/30000);
    } 
    return 0;
}

