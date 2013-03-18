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

	public:
		Polygon(void) : randomFill(false), fill(NULL), PolyLine() { };
		Polygon(bool _randomFill) : randomFill(_randomFill), fill(NULL), PolyLine() { };
		Polygon(Colors::rgba *_fill) : randomFill(false), fill(_fill), PolyLine() { };
		~Polygon(void);

		virtual void add(Line* line);
		virtual void close();
		virtual void draw();
	};

}

#endif