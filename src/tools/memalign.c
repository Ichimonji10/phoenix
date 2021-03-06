/****************************************************************************
FILE      : memalign.c
SUBJECT   : Memory alignment
PROGRAMMER: (C) Copyright 2008 The Phoenix Team.

Aligns the memory of a com file. Outputs a new file called bloader.bin.

Please send comments or bug reports to

    Phoenix Team
    c/o Peter C. Chapin
    Vermont Technical College
    Randolph Center, VT 05061
    PChapin@vtc.vsc.edu
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) 
{
    FILE *input_fp, *output_fp;
    int i, data;
	
    if( argc != 2 ) {
        printf("Incorrect number of arguments!\nMust use: %s [input_file].\n", argv[0] );
        return 1;
    }
    
    /* Open the input file */
    if( ( input_fp = fopen( argv[1], "rb" ) ) == NULL ) {
        printf( "Error opening file %s for reading.\n", argv[1] );
        exit( 1 );
    }
  
    /* Open the output file */
    if( ( output_fp = fopen( "bloader.com", "wb" ) ) == NULL ) {
        printf( "Error opening file bloader.com for writing.\n" );
        exit( 1 );
    }
  
    /* Fill up the first 256 bytes of the output file. */
    for( i = 0; i < 256; i++ ) {
        putc( 0x90, output_fp );
    }
  
    /* Copy the input file after the first 256 bytes. */
    while( ( data = getc( input_fp ) ) != EOF ) {
        putc( data, output_fp );
    }
  
    fclose( input_fp );
    fclose( output_fp );
    return 0;
}

