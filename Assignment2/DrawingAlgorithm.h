/*
 *	DrawingAlgorithm.h
 *
 *	Created on : Jan 26, 2013
 *  Course     : CS4610/7610
 *  Instructor : Kannappan Palaniappan
 *	Author	   : Rui Wang
 *	Purpose    : Define all drawing functions.
 *
 *	Copyright University of Missouri-Columbia
 */


#pragma once
#ifndef DRAWINGALGORITHMS_H
#define DRAWINGALGORITHMS_H
#include "declarations.h"

class DrawingAlgorithms
{
public:
    /*<<<<<<<<<<<<<<<<<<<<<drawline>>>>>>>>>>>>>>>>>>>>>>>>
	 Insert your comments here
	 */

	static void BresenhamLine(int xs, int ys, int xe, int ye,
	float lineThickness, LineStyle::Style lineStyle, Colors::rgba rgba,
	Fl_Text_Display * textDisplay, bool print);
	
};
#endif
