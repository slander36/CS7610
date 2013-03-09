/*
 *	Author	: Sean Lander
 *	Purpose	: Circle Header. Creates and draws a Circle.
 *	Created	: 2013-02-20
 *
 *	Copyright Sean Lander, all rights reserved
 */

#pragma once
#ifndef _SL_CIRCLE_H
#define _SL_CIRCLE_H

#include "Shape.h"

class Circle : public Shape {

private:
	int x, y, r;

public:
	Circle(void) : 
		x(0), y(0), r(10),
		Shape()
	{ };

	Circle(int n_x, int n_y, int n_r) :
		x(n_x), y(n_y), r(n_r),
		Shape()
	{ };

	Circle(int n_x, int n_y, int n_r, float n_lineThickness, LineStyle::Style n_style) :
		x(n_x), y(n_y), r(n_r),
		Shape(n_lineThickness, n_style)
	{ };

	Circle(int n_x, int n_y, int n_r, float n_lineThickness, LineStyle::Style n_style, Fl_Text_Display* n_textDisplay, bool n_print, Colors::rgba n_rgba) :
		x(n_x), y(n_y), r(n_r),
		Shape(n_lineThickness, n_style, n_textDisplay, n_print, n_rgba)
	{ };

	~Circle(void) { };

	/* Getters and Setters */
	void setX(int n_x) { x = n_x; };
	int getX() { return x; };

	void setY(int n_y) { y = n_y; };
	int getY() { return y; };

	void setCenter(int n_x, int n_y) { setX(n_x); setY(n_y); };

	void setR(int n_r) { r = n_r; };
	int getR() { return r; };

	/* Draw Function */

	void draw();
	void setPixel(int xo, int yo, int step);

};

#endif
