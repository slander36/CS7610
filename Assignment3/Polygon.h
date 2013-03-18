#pragma once
#ifndef _SL_POLYGON_H
#define _SL_POLYGON_H

#include "polyline.h"
#include <map>

namespace sldraw {

	class Polygon : public PolyLine {
	private:

		bool randomFill;
		Colors::rgba *fill;
		bool printSET;
		bool printAET;
		Fl_Text_Display *textDisplay;

	public:
		Polygon(void) :
			randomFill(false), fill(NULL), printSET(false), printAET(false), textDisplay(NULL),
			PolyLine()
		{ };
		Polygon(bool _randomFill) :
			randomFill(_randomFill), fill(NULL), printSET(false), printAET(false), textDisplay(NULL),
			PolyLine()
		{ };
		Polygon(Colors::rgba *_fill) :
			randomFill(false), fill(_fill), printSET(false), printAET(false), textDisplay(NULL),
			PolyLine()
		{ };
		Polygon(bool _randomFill, bool _printSET, bool _printAET, Fl_Text_Display *_textDisplay) :
			randomFill(_randomFill), fill(NULL), printSET(_printSET), printAET(_printAET), textDisplay(_textDisplay),
			PolyLine()
		{ };
		Polygon(Colors::rgba *_fill, bool _printSET, bool _printAET, Fl_Text_Display *_textDisplay) :
			randomFill(false), fill(_fill), printSET(_printSET), printAET(_printAET), textDisplay(_textDisplay),
			PolyLine()
		{ };
		~Polygon(void);

		virtual void draw();
	};

}

#endif