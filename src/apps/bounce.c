/****************************************************************************
FILE          : bounce.c
LAST REVISION : 2008-04-22
SUBJECT       : Message based breakout game.
PROGRAMMER    : (C) Copyright 2008  The Phoenix Team.

Message based breakout game.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include "xtimer.h"
#include "message.h"
#include "vparser.h"
#include "xvideo.h"
#include "video.h"
#include "vga.h"
#include <conio.h>
#include "keyboard.h"
#include "beep.h"
#include "kparser.h"
#include "xkeyboard.h"

#define RIGHT 0
#define LEFT 1
#define NONE 2

#define TRACE_COLUMN 60
#define COLOR 0x04

int trace_counter = 0;

processID vidid;
processID mainid;
processID keyid;
processID hackid;

void *main_thread(void);
void *hack(void);

//This is a startup intro for the console
void intro()
{
    //The palette will change when pu_image is called, so the color values have to be based on that palette
    xvideo_rect_fill(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 0xCD);
    xvideo_put_image(120, 60, "phoenix");
    xvideo_circle(160, 95, 60, 0xAC);
    beep(C5);
    beep(A4S);
    beep(F4);
    beep(C5);
    beep(A4S);
    beep(F4);
    beep(C5);
    beep(A4S);
    beep(F4);
    beep(C5);
    beep(A4S);
    beep(F4);
    beep(C5);
    beep(C5);
    beep(C5);
    while(getKey() == 0) { } //Press any key to continue
}


int main(void)
{
    vidid.pid = VIDEO;
    mainid.pid = MAIN;
    keyid.pid = KEYBOARD;
    hackid.pid = 4;
	
    clear_screen();
    disable_interrupts();
  
    //initialize_timer_frequency();
    initialize_keyboardISR();
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
  
    if (xthread_create(mainid, main_thread)) {
        print_at(trace_counter++, TRACE_COLUMN, "Failed to create main thread", COLOR);
    }
    else {
        print_at(trace_counter++, TRACE_COLUMN, "Created test thread", COLOR);
    }
  
    enable_interrupts();
  
    print_at(trace_counter++, TRACE_COLUMN, "Looping in main", COLOR);
    for (;;) { }
    print_at(trace_counter++, TRACE_COLUMN, "SHOULD NEVER SEE THIS!", COLOR);
    return 0;
}


void *main_thread(void)
{
    char myLastKey, direction;
    unsigned int i, j, color, timerCount;
    int paddleX, pixelX, pixelY, pixelSlopeX, pixelSlopeY, paddleWidth, paddleHeight, curLocColor, blockCount;
  
    set_mode(VGA_MODE);
  
    intro();
restart:
    //Initialization
    clear_screen(); 
    direction    = NONE;
    color        = 32;
    timerCount   = 0;
    paddleX      = 150;
    pixelX       = 319;
    pixelY       = 100;
    pixelSlopeX  = 1;
    pixelSlopeY  = -1;
    paddleWidth  = 20;
    paddleHeight = 5;
    curLocColor  = 0;
    blockCount   = 12 * 16;
    
    xvideo_rect_fill(paddleX, SCREEN_HEIGHT-1-paddleHeight, paddleX+paddleWidth, SCREEN_HEIGHT-1, 4);
    //xvideo_rect_fill(0, SCREEN_HEIGHT-1-paddleHeight, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 4);
    xvideo_put_pixel(pixelX, pixelY, 0x0F);
    
    //Create blocks
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 16; j++) {
            xvideo_rect_fill(j*20, i*6, j*20+19, i*6+5, color);
        }
        color++;
    }
    
    while(1) {
        //Get key press
        myLastKey = getKey();
        if (myLastKey == 75) {
            direction = LEFT;
        }
        else if (myLastKey == 77) {
            direction = RIGHT;
        }
        else if (myLastKey == 80) {
            direction = NONE;
        }
    
        //Move paddle
        if (direction == LEFT && paddleX > 0) {
            paddleX--;
        }
        else if (direction == RIGHT && paddleX+paddleWidth < SCREEN_WIDTH-1) {
            paddleX++;
        }
    
        //Show paddle
        if (direction == LEFT) {
            xvideo_line(paddleX, SCREEN_HEIGHT-1-paddleHeight, paddleX, SCREEN_HEIGHT-1, 4);
            if (paddleX+paddleWidth+1 <= SCREEN_WIDTH-1) {
                xvideo_line(paddleX+paddleWidth+1, SCREEN_HEIGHT-1-paddleHeight, paddleX+paddleWidth+1, SCREEN_HEIGHT-1, 0);
            }
        }
        if (direction == RIGHT) {
            xvideo_line(paddleX+paddleWidth, SCREEN_HEIGHT-1-paddleHeight, paddleX+paddleWidth, SCREEN_HEIGHT-1, 4);
            if (paddleX-1 >= 0) {
                xvideo_line(paddleX-1, SCREEN_HEIGHT-1-paddleHeight, paddleX-1, SCREEN_HEIGHT-1, 0);
            }
        }
    
        //Only move the ball every other count
        if (timerCount%2 == 0) {
            //Erase ball
            xvideo_put_pixel(pixelX, pixelY, 0x00);
            //Calculate position
            if (pixelY + pixelSlopeY < 0) {
                pixelSlopeY = -pixelSlopeY;
            }
            else if (pixelY + pixelSlopeY > SCREEN_HEIGHT-1) {
                break;
            }
            if (pixelX + pixelSlopeX > SCREEN_WIDTH-1 || pixelX + pixelSlopeX < 0) {
                pixelSlopeX = -pixelSlopeX;
            }
            
            //Check color
            if ((curLocColor = get_pixel(pixelX + pixelSlopeX, pixelY + pixelSlopeY)) != 0x00) {
                //We hit a color
                if (curLocColor == 0x04) {
                    pixelSlopeY = -pixelSlopeY;
                }
                else {
                    //Remove block
                    xvideo_rect_fill((pixelX + pixelSlopeX)/20*20, (pixelY + pixelSlopeY)/6*6, 
                                     (pixelX + pixelSlopeX)/20*20+19, (pixelY + pixelSlopeY)/6*6+5, 0x00);
                    blockCount--;
                    if (blockCount == 0) {
                        break;
                    }
                    //Check corners
                    if ((pixelX + pixelSlopeX)%20 == 0 && (pixelY + pixelSlopeY)%6 == 0 && pixelSlopeX == 1 && pixelSlopeY == 1 || 
                        (pixelX + pixelSlopeX)%20 == 0 && (pixelY + pixelSlopeY)%6 == 5 && pixelSlopeX == 1 && pixelSlopeY == -1  ||
                        (pixelX + pixelSlopeX)%20 == 19 && (pixelY + pixelSlopeY)%6 == 0 && pixelSlopeX == -1 && pixelSlopeY == 1  ||
                        (pixelX + pixelSlopeX)%20 == 19 && (pixelY + pixelSlopeY)%6 == 5 && pixelSlopeX == -1 && pixelSlopeY == -1) {
                        pixelSlopeX = -pixelSlopeX;
                        pixelSlopeY = -pixelSlopeY;
                    }
                    else if ((pixelY + pixelSlopeY)%6 != 0 && (pixelY + pixelSlopeY)%6 != 5) {
                        pixelSlopeX = -pixelSlopeX;
                    }
                    else {
                        pixelSlopeY = -pixelSlopeY;
                    }
                }
            }
            pixelY += pixelSlopeY;
            pixelX += pixelSlopeX;
      
            //Show Ball
            xvideo_put_pixel(pixelX, pixelY, 0x0F);
        }
    
        //Delay
        for (i = 0; i < 1000; i++) {
            for (j = 0; j < 2000; j++) { }
        }
    
        timerCount++;
    }
    if (blockCount < 0) {
        xvideo_vga_print_at(11, 16, "You Win!", 0x07);
    }
    else {
        xvideo_vga_print_at(11, 15, "Game Over", 0x07);
    }
    while(getKey() == 0) {} //Press any key to continue
    goto restart;
  
    return NULL;
}


void *hack(void)
{
    while(1) { }
    return NULL;
}

