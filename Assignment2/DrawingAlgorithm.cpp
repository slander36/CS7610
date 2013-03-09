/*
 *	DrwaingAlgorithm.cpp
 *
 *	Created on : Jan 26, 2013
 *  Course     : CS4610/7610
 *  Instructor : Kannappan Palaniappan
 *	Author	   : Rui Wang
 *	Purpose    : Implement all drawing algoritms (eg. Bresenham line and circle) 
 *
 *
 *	Updated By : Sean Lander
 *	Updated On : Feb 03, 2013
 *
 *	Copyright University of Missouri-Columbia
 */


#include "DrawingAlgorithm.h"
#include <FL/gl.h>
#include <FL/Fl_Text_Buffer.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>


void DrawingAlgorithms::BresenhamLine(int xs, int ys, int xe, int ye,
	float lineThickness, LineStyle::Style lineStyle, Colors::rgba rgba,
	Fl_Text_Display * textDisplay, bool print
	) {

	/* Set Line Thickness */
	glPointSize(lineThickness);

	/* Set Draw Color */
	glColor4f(rgba.red, rgba.green, rgba.blue, rgba.alpha);

	glBegin(GL_POINTS);	

	/* Bresenham's Algorithm */

	// Get all static values
	int deltaX = abs(xe - xs);
	int deltaY = abs(ye - ys);
	bool steep = deltaY > deltaX;
	bool negativeY = (ye - ys) < 0;
	bool negativeX = (xe - xs) < 0;

	// Get all conditional values
	int update0, update1, d;
	// If the line is steep the decision
	// is between N and NE pixel as opposed
	// to the E and NE pixel.
	// The initial decision variable should
	// reflect this as well.
	if( steep ) {
		update0 = deltaX<<1;
		update1 = (deltaX<<1) - (deltaY<<1);
		d = (deltaX<<1) - deltaY;
	} else {
		update0 = deltaY<<1;
		update1 = (deltaY<<1) - (deltaX<<1);
		d = (deltaY<<1) - deltaX;
	}

	// Get looping variables
	// If the line is steep, swap x and y
	// so the decision is between N and NE
	// pixels as opposed to E and NE
	int x = (steep ? ys : xs);
	int y = (steep ? xs : ys);

	/* Print Variables */

	Fl_Text_Buffer * textBuffer = NULL;
	if( print ) {
		textBuffer = textDisplay->buffer();
		textBuffer->append("Line: ");
	}

	/* Create Draw Mask */

	LineStyle::DrawMask* p_DrawMask = LineStyle::getDrawMask(lineStyle);
	int *drawMask = p_DrawMask->drawMask;
	int drawMaskSize = p_DrawMask->drawMaskSize;
	int drawMaskIndex = 0;

	/*

	int *drawMask;
	int drawMaskSize;
	int drawMaskIndex = 0;

	switch(lineStyle) {
		case LineStyle::DASHES:
			drawMaskSize = 8;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1; drawMask[2] = 1; drawMask[3] = 1;
			drawMask[4] = 0; drawMask[5] = 0; drawMask[6] = 0; drawMask[7] = 0;
			break;
		case LineStyle::DOTS:
			drawMaskSize = 4;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1;
			drawMask[2] = 0; drawMask[3] = 0;
			break;
		case LineStyle::MIXED:
			drawMaskSize = 10;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1; drawMask[2] = 1; drawMask[3] = 1;
			drawMask[4] = 0; drawMask[5] = 0;
			drawMask[6] = 1; drawMask[7] = 1;
			drawMask[8] = 0; drawMask[9] = 0;
			break;
		case LineStyle::SOLID:
		default:
			drawMaskSize = 1;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1;
	}

	*/

	// Loop
	int steps = (steep ? deltaY : deltaX );
	for( int i = 0 ; i < steps ; i++ ) {
		// If the line is steep, then x and y
		// have been swapped. This must be accounted
		// for before drawing anything.
		if( steep ) {
			// If print is set to True...
			if( print && textBuffer != NULL) {
				std::stringstream ostream;
				ostream << "(" << y << "," << x << ") ";
				textBuffer->append(ostream.str().c_str());
			}
			// Draw the pixel
			if( drawMask[drawMaskIndex] ) glVertex2i(y,x);
			drawMaskIndex = (++drawMaskIndex)%drawMaskSize;

			// x and y were swapped, so check the
			// correct negative flag
			x = (negativeY ? x-1 : x+1);
		} else {
			// If print is set to True...
			if( print && textBuffer != NULL) {
				std::stringstream ostream;
				ostream << "(" << x << "," << y << ") ";
				textBuffer->append(ostream.str().c_str());
			}
			// Draw the pixel
			if( drawMask[drawMaskIndex] ) glVertex2i(x,y);
			drawMaskIndex = (++drawMaskIndex)%drawMaskSize;

			// Inc or Dec x depending on direction of drawing
			x = (negativeX ? x-1 : x+1);
		}
		// If d is negative, then next pixel to
		// fill in is East (generically speaking)
		// otherwise, North East.
		if( d < 0 ) {
			d+=update0;
		} else {
			// x and y were swapped so check the
			// correct negative flag
			if( steep ) {
				y = (negativeX ? y-1 : y+1);
			} else {
				y = (negativeY ? y-1 : y+1);
			}
			d+=update1;
		}
	}
	// Print the final value
	if( steep ) glVertex2i(y,x); else glVertex2i(x,y);

	if( print && textBuffer != NULL) {
		std::stringstream ostream;
		if( steep) {
			ostream << "(" << y << "," << x << ")\n";
		} else {
			ostream << "(" << x << "," << y << ")\n";
		}
		textBuffer->append(ostream.str().c_str());
	}

	/* Free LineMask */
	free(drawMask);
	free(p_DrawMask);

	/* End Bresenham */

	glEnd();

	/* Reset Color */
	glColor4f(1.0,1.0,1.0,1.0);

	/* Reset Pixel Size */
	glPointSize(1.0);
}

