/*
 *	Author	: Sean Lander
 *	Purpose	: Line class header. Used to create, store and draw lines
 *	Created	: 2013-02-10
 *
 *	Copyright Sean Lander, all rights reserved
 */

#pragma once
#ifndef _SL_LINE_H
#define _SL_LINE_H

#include "Object.h"

class Line : public Object {

private:
	int xs, xe, ys, ye;
	float lineThickness;
	LineStyle::Style lineStyle;

public:
	/* Constructor */
	Line() :
		xs(0), xe(0), ys(0), ye(0),
		lineThickness(1.0), lineStyle(LineStyle::SOLID),
		Object()
	{ };

	Line(int n_xs, int n_ys, int n_xe, int n_ye) :
		xs(n_xs), ys(n_ys), xe(n_xe), ye(n_ye),
		lineThickness(1.0), lineStyle(LineStyle::SOLID),
		Object()
	{ };

	Line(int n_xs, int n_ys, int n_xe, int n_ye, float n_lineThickness, LineStyle::Style n_style) :
		xs(n_xs), ys(n_ys), xe(n_xe), ye(n_ye),
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object()
	{ };

	Line(int n_xs, int n_ys, int n_xe, int n_ye, float n_lineThickness, LineStyle::Style n_style, Fl_Text_Display* n_textDisplay, bool n_print, Colors::rgba n_rgba) :
		xs(n_xs), ys(n_ys), xe(n_xe), ye(n_ye),
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object(n_textDisplay, n_print, n_rgba)
	{ };

	// In case of doubles...

	Line(double n_xs, double n_ys, double n_xe, double n_ye) :
		xs(round(n_xs)), ys(round(n_ys)), xe(round(n_xe)), ye(round(n_ye)),
		lineThickness(1.0), lineStyle(LineStyle::SOLID),
		Object()
	{ };

	Line(double n_xs, double n_ys, double n_xe, double n_ye, float n_lineThickness, LineStyle::Style n_style) :
		xs(round(n_xs)), ys(round(n_ys)), xe(round(n_xe)), ye(round(n_ye)),
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object()
	{ };

	Line(double n_xs, double n_ys, double n_xe, double n_ye, float n_lineThickness, LineStyle::Style n_style, Fl_Text_Display* n_textDisplay, bool n_print, Colors::rgba n_rgba) :
		xs(round(n_xs)), ys(round(n_ys)), xe(round(n_xe)), ye(round(n_ye)),
		lineThickness(n_lineThickness), lineStyle(n_style),
		Object(n_textDisplay, n_print, n_rgba)
	{ };
	

	~Line() { };

	/* Getters and Setters */

	void setxs(int n_xs) { xs = n_xs; };
	int getxs() { return xs; };

	void setys(int n_ys) { ys = n_ys; };
	int getys() { return ys; };

	void setStartPoint(int n_xs, int n_ys) { setxs(n_xs); setys(n_ys); };

	void setxe(int n_xe) { xe = n_xe; };
	int getxe() { return xe; };

	void setye(int n_ye) { ye = n_ye; };
	int getye() { return ye; };

	void setEndPoint(int n_xe, int n_ye) { setxe(n_xe); setye(n_ye); };

	void setLineThickness(float n_lineThickness) { lineThickness = n_lineThickness; };
	float getLineThickness() { return lineThickness; };

	void setLineStyle(LineStyle::Style n_lineStyle) { lineStyle = n_lineStyle; };
	LineStyle::Style getLineStyle() { return lineStyle; };

	/* Draw Method */
	void draw();
	void draw(Colors::rgba rgbas, Colors::rgba rgbae);

};

#endif
