/*
 *	Author	: Sean Lander
 *	Purpose	: Base object class for all future drawings
 *	Created	: 2013-02-10
 *
 *	Copyright Sean Lander, all rights reserved
 */

#pragma once
#ifndef _SL_OBJECT_H_
#define _SL_OBJECT_H_

#include "declarations.h"
#include <FL/gl.h>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

class Object {

protected:
	Fl_Text_Display* textDisplay;
	bool print;

	Colors::rgba rgba;
	
public:
	/* Virtual Functions */
		
	Object( void ) :
		textDisplay((Fl_Text_Display*)NULL), print(false), rgba(Colors::ColorArray[Colors::WHITE])
	{ };
	Object( Fl_Text_Display* n_textDisplay ) :
		textDisplay(n_textDisplay), print(false), rgba(Colors::ColorArray[Colors::WHITE])
	{ };
	Object( Fl_Text_Display* n_textDisplay, bool n_print ) :
		textDisplay(n_textDisplay), print(n_print), rgba(Colors::ColorArray[Colors::WHITE])
	{ };
	Object( Fl_Text_Display* n_textDisplay, bool n_print, Colors::rgba n_rgba) :
		textDisplay(n_textDisplay), print(n_print), rgba(n_rgba)
	{ };

	~Object() { };

	/* Getters and Setters */

	void setTextDisplay(Fl_Text_Display* n_textDisplay) { textDisplay = n_textDisplay; };
	Fl_Text_Display* getTextDisplay() { return textDisplay; };

	void setPrint(bool n_print) { print = n_print; };
	bool getPrint() { return print; };

	void setColor(Colors::rgba n_rgba) { rgba = n_rgba; };
	Colors::rgba getColor() { return rgba; };

	/* Draw Function - Virtual */

	virtual void draw() = 0;
};

#endif
