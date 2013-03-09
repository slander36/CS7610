/*
 *	Author	: Sean Lander
 *	Purpose	: Shape Header. Base class for other shapes.
 *	Created	: 2013-02-20
 *
 *	Copyright Sean Lander, all rights reserved
 */

#pragma once
#ifndef _SL_SHAPE_H
#define _SL_SHAPE_H

#include "Object.h"
class Shape : public Object {

private:
	float lineThickness;
	LineStyle::Style lineStyle;

public:
	Shape(void) :
		lineThickness(1.0), lineStyle(LineStyle::SOLID),
		Object()
	{ };

	Shape(float n_lineThickness, LineStyle::Style n_style) :
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object()
	{ };

	Shape(float n_lineThickness, LineStyle::Style n_style, Fl_Text_Display* n_textDisplay, bool n_print, Colors::rgba n_rgba) :
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object(n_textDisplay, n_print, n_rgba)
	{ };

	~Shape(void) { };

	/* Getters and Setters */

	void setLineThickness(float n_lineThickness) { lineThickness = n_lineThickness; };
	float getLineThickness() { return lineThickness; };

	void setLineStyle(LineStyle::Style n_lineStyle) { lineStyle = n_lineStyle; };
	LineStyle::Style getLineStyle() { return lineStyle; };

	/* Virtual Draw Function */

	virtual void draw() = 0;

};

#endif

