
/**************************************************************************/
/*                                                                        */
/*                                                                        */
/*                            SCREEN ROUTINE MODULE		                  */
/*                                                                        */
/*                                     by                                 */
/*                                                                        */
/*                                 L. J. Sciacca                          */
/*         Department of Electrical Engineering and Computer Science      */
/*                            University of Newcastle					  */
/*									Austraila                             */
/*                                                                        */
/*                         ( Copyright 90, 91 )                           */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/*
	HISTORY

	Began this module around July 1990. Built up as needs developed.
	L. J. Sciacca

	Latest: 20-April-1991 LJS, added Module description.

*/


/*
	MODULE DESCRIPTION

	Routines to do higher level writing to PC screen using the standard
screen codes. Functions include drawing boxes and simple bar graph
facilities.

	Note that for efficiency, the TurboC extern define of _direct_video
should be placed in the main program to ensure no BIOS calls are made on
printing to the screen.

	The following routines have been provided:

	pcscr_put_text ( )	- place text at point (x,y) with specified type
	pcscr_put_double ( )- place a double at point (x,y)
	pcscr_put_int ( )	- place an integer at point (x,y)
	pcscr_draw_line ( )	- draw a line from point A to B ( hor, ver )
	pcscr_draw_box ( )	- draw a rectangle box
	pcscr_corner ( )	- put a corner
	pcscr_draw_bar ( )	- draw bar graphs

	this file has been blessed by tzqh & ksc :) 14/3/96
*/

#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "general.h"
#include "pcscr.h"

static void test_make_box ( void );

static char * farr []={"MAIN", "ORBIT ", "CALIB ", "TUNE  ", "PARSER", "INTELS" };
/*
****************************************************************************
test_make_box

	This routine demonstrates how to use the draw line, draw corner routines

***************************************************************************
*/
//void main ( void ) {
// test_make_box ( );
//}

void test_make_box ( ) {

	clrscr ( );
	/* draw a box */
/*	pcscr_draw_line ( 30, 2, 10, HOR, 1 );
	pcscr_draw_line ( 10, 32, 10, VER, 1 );
	pcscr_draw_line ( 30, 32, 20, HOR, -1 );
	pcscr_draw_line ( 10, 2, 20, VER, -1 );

	pcscr_corner ( 32, 10, UPPERRIGHT );
	pcscr_corner ( 32, 20, LOWERRIGHT );
	pcscr_corner ( 2, 20, LOWERLEFT );
	pcscr_corner ( 2, 10, UPPERLEFT );
*/
	pcscr_draw_box ( 2, 2, 20, 5, "Hello Box", BOLD );

	pcscr_function_menu ( 6, farr );

} // end of test_make_box


/*
****************************************************************************
pcscr_function_menu

	Routine to put function key across bottom of screen.

***************************************************************************
*/
void pcscr_function_menu ( unsigned int number_of_keys, char * farray[]) {

	int i, j;
	char string [10];
	char temp [ 10 ];

	j = 1;
	string [0]=NULL;

	for ( i=1; i< number_of_keys+1; i++ ) {

		strcat ( string, "F" );
		strcat ( string, itoa(i, temp, 10) );
		strcat ( string, "-" );
		strcat ( string, farray[i-1] );

		/* prints the function commands on line 24  :) 14/3/96 */
		pcscr_put_text ( j, 24, string, BOLD );
		j = j + 10;  /* increments the spaces for next function printout :) 14/3/96 */
		string [0]=NULL;
		}


} // end of pcscr_function_menu


/*
****************************************************************************
pcscr_put_text

	This routine adds text to the PC screen at coordinates x,y. Remember
that the allowable positions must be within the box 1,1 - 80,25.
This routine allows the setting of different text attributes.

	Presently only bold and normal are provided for.

***************************************************************************
*/
void pcscr_put_text ( unsigned int x, unsigned int y,
					char * text, unsigned int mode ) {

	gotoxy ( x, y );
	switch ( mode ) {

		case normal:
			break;

		case bold:
			highvideo ( );
			break;

		default:
			break;
		}

	cprintf ( "%s", text );

	//if ( mode != normal )
		//normvideo ( );

} /* end of pcscr_put_text */


/*
****************************************************************************
pcscr_put_double

	This routine adds a double value to the PC screen at coordinates x,y. Remember
that the allowable positions must be within the box 1,1 - 80,25.
This routine allows the setting of different text attributes.

	The format of the value is passed as a string to the routine.

***************************************************************************
*/
void pcscr_put_double ( unsigned int x, unsigned int y,
					char * fmt, double dble, unsigned int mode ) {

	gotoxy ( x, y );

	switch ( mode ) {

		case normal:
			break;

		case bold:
			highvideo ( );
			break;

		default:
			break;
		}

	cprintf ( fmt, dble );

	if ( mode != normal )
		normvideo ( );

} /* end of pcscr_put_double */


/*
****************************************************************************
pcscr_put_int

	This routine places an integer value to the PC screen at coordinates x,y. Remember 
that the allowable positions must be within the box 1,1 - 80,25.
This routine allows the setting of different text attributes.

	The format of the value is passed as a string to the routine.

Parameters:
	x = unsigned int x position
	y = unsigned int y position
	fmt = string specifying the format of output
	mode = unsigned int specifyinh mode, NORMAL, BOLD.
***************************************************************************
*/
void pcscr_put_int ( unsigned int x, unsigned int y, 
					char * fmt, int intval, unsigned int mode ) {

	gotoxy ( x, y );

	switch ( mode ) {

		case NORMAL:
			break;

		case BOLD:
			highvideo ( );
			break;

		default:
			break;
		}

	cprintf ( fmt, intval );

	if ( mode != normal )
		normvideo ( );

} /* end of pcscr_put_int */


/*
==========================================================================
	pcscr_draw_line

	Routine to draw a line on the Screen.

==========================================================================
*/
void pcscr_draw_line ( unsigned int length, unsigned int x, 
						unsigned int y, int dir, int move ) {

	unsigned int i;

	if ( dir == HOR )
		{
		for ( i=0; i < length ; i++ ) {
			gotoxy ( x, y );
			x += move;
			cprintf ( "\xc4" );
			}
		}
	else
		{
		for ( i=0; i < length+1; i++ )
			{
			gotoxy ( x, y );
			cprintf ( "\xb3" );
			y = y + move;
			}
		}

} /* end of draw_line */


/*
==========================================================================
	pcscr_corner

	Routine to place a corner figure. These are �, � etc.

==========================================================================
*/
void pcscr_corner ( unsigned int x, unsigned int y, unsigned int corner ) {


	gotoxy ( x, y );

	switch ( corner )
		{
		case LOWERRIGHT:
					cprintf ( "\xd9" );
					break;

		case UPPERRIGHT:
					cprintf ( "\xbf" );
					break;

		case UPPERLEFT:
					cprintf ( "\xda" );
					break;

		case LOWERLEFT:
					cprintf ( "\xc0" );
					break;

		case TLEFT:
					cprintf ( "\xc3" );
					break;

		case TRIGHT:
					cprintf ( "\xb4" );
					break;

		case TDOWN:
					cprintf ( "\xc2" );
					break;

		case TUP:
					cprintf ( "\xc1" );
					break;

		case INTERSECT:
					cprintf ( "\xc1" );
					break;

		default:break;
		}

} /* end of pcscr_corner */


/*
============================================================================
	pcscr_draw_box ( )

	Routine to draw a 2D box.

	Draw a box:
	xs,ys
	-------------------------
	|						| yfin-ys
	|						| 
	------------------------- (xfin,yfin)
		xfin-xs

Parameters passed: 	- box x start, box y start positions
					- box x finish, box y finish
					- box title ( if NULL, no title box is given )

============================================================================
*/
void pcscr_draw_box ( unsigned int xstart, unsigned int ystart,
					unsigned int xfinish, unsigned int yfinish, 
					char* title, unsigned int mode ) {

	unsigned int xlength, xend;
	unsigned int ylength, yend;

	xlength = xfinish - xstart;
	ylength = yfinish - ystart;
	xend = xstart + xlength;
	yend = ystart + ylength;

	/* Draw a box */
	pcscr_draw_line ( xlength, xstart, ystart, HOR, 1 );
	pcscr_draw_line ( ylength, xend, ystart, VER, 1 );
	pcscr_draw_line ( xlength, xend, yend, HOR, -1 );
	pcscr_draw_line ( ylength, xstart, yend, VER, -1 );

	/* Put the corners on */
	pcscr_corner ( xend, ystart, UPPERRIGHT );
	pcscr_corner ( xend, yend, LOWERRIGHT );
	pcscr_corner ( xstart, yend, LOWERLEFT );
	pcscr_corner ( xstart, ystart, UPPERLEFT );

	/* Put title in box if there is one */
	if ( title != NULL ) {
		gotoxy ( xstart+1, ystart+1 );

		switch ( mode ) {
			case normal:
				break;

			case bold:
				highvideo ( );
				break;

			default:
				break;
			}

		cprintf ( "%s", title );

		//if ( mode != normal )
		  //	normvideo ( );

		}

} /* end of pcscr_draw_box */


/*
============================================================================
	pcscr_draw_bar

	Routine to draw a bar either up or down.

	Pivot is intended for when this is expanded to allow bars from different
	pivot positions.

	Draw a bar:
	xs,ys


	���������������������������������
	<---fraction of value to max---->

	<------------------------------------------------------->
		length equates to max_value

	Parameters passed:
		label = 3 character description of bar
		value = value to plot
		pivot = starting point relative to (usually 0)
		max_value = maximum value to determine fraction of bar
		xstart = pivot position of bar on the screen
		ystart = pivot position of bar on screen
		direction = vertical (VER) or horizontal (HOR) bar
		length = length of x or y axis on the screen
		char_type = character to draw bar with (usually HASH)

		>>>>> N.B. Pivot facility not used yet. <<<<<<

============================================================================
*/

void pcscr_draw_bar ( char * label, double value,
					double pivot, double max_value,
					unsigned int xstart, unsigned int ystart,
					int direction, unsigned int length ) {

	unsigned int i;
	unsigned int x, xinc, q_sign;
	unsigned int y, yinc;
	unsigned int xl_off, yl_off, x_off, y_off;

	double value_tmp, quantum;

	/* I need to remove this pivot variable, assign to zero to remove warning */
	pivot = 0;

	if ( ( direction == VER ) && (pivot == 0 ) ) {
		xinc = 0;
		yinc = 1;
		xl_off = 0;
		yl_off = -1;
		x_off = 0;
		y_off = 0;
		}
	else {
		xinc = 1;
		yinc = 0;
		xl_off = 4;
		yl_off = 0;
		x_off = 10;
		y_off = 0;
		}

	x = xstart;
	y = ystart;

	/* write bar label */
	pcscr_put_text ( xstart, ystart, label, BOLD );
	gotoxy ( xstart + xl_off, ystart + yl_off );
	cprintf ( "%5.1f", value );

	quantum = max_value/length;
	if ( quantum > 0 )
		q_sign = 1;
	else
		q_sign = -1;

	value_tmp = 0;

	/* Clear old bar and make new. This is not very efficient. Ideally
		we want to just add or subtract from original. For the number of
		bars however that will be build up, this should not be too bad
		considering the overhead involved in calculating vanishing bars and
		growing ones.
	*/
	for ( i = 0; i < length; i++ ) {
		if ( direction == HOR )
			gotoxy ( x + x_off + i, y + y_off );
		else
			gotoxy ( x + x_off, y + y_off - i );

		cprintf ( " " );
		}

	while ( fabs(value_tmp) < fabs(value) ) {

		gotoxy ( x + x_off, y + y_off );
		cprintf ( "\xb1" );

		x = x + ( xinc * q_sign );
		y = y + ( yinc * q_sign );

		value_tmp = value_tmp + quantum;

		} /* while */

} /* end of pcscr_draw_bar */


/*---------------------------------------------------------------------

			Draw Horizontal Bar
													- has a label
													- start x position
													- end x position
													- x,y co-ordinate
-----------------------------------------------------------------------*/


void pcscr_draw_hor_bar ( double value, double max_value
													, unsigned int xstart, unsigned int ystart
													, unsigned int length ) {

	unsigned int i;
	unsigned int x, xinc, q_sign;
	unsigned int y, yinc;
	unsigned int xl_off, yl_off, x_off, y_off;

	double value_tmp, quantum;

/* sets to horizontal type bar */
		xinc = 1;
		yinc = 0;

	x = xstart;
	y = ystart;

	quantum = max_value/length;
	if ( quantum > 0 )
		q_sign = 1;
	else
		q_sign = -1;

	value_tmp = 0;

	/* Clear old bar and make new. This is not very efficient. Ideally
		we want to just add or subtract from original. For the number of
		bars however that will be build up, this should not be too bad
		considering the overhead involved in calculating vanishing bars and
		growing ones.
	*/
	for ( i = 0; i < length; i++ ) {

		gotoxy ( x + i, y);
		cprintf ( " " );

		}

	while ( fabs(value_tmp) < fabs(value) ) {

		gotoxy ( x, y);
		cprintf ( "\xb1" );

		x = x + ( xinc * q_sign );
		y = y + ( yinc * q_sign );

		value_tmp = value_tmp + quantum;

		} /* while */

} /* end of pcscr_draw_hor_bar */

/*
============================================================================
restore_pc_screen

	Routine to clear the screen and restore cursor.

============================================================================
*/
void restore_pc_screen ( void ) {

	clrscr ( );
	_setcursortype ( _NORMALCURSOR );

} /* end of restore_ps_screen */

