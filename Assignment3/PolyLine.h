#pragma once
#ifndef _SL_POLYLINE_
#define _SL_POLYLINE_

#include "Shape.h"
#include "Line.h"
#include <list>

class PolyLine : public Shape {

private:
	std::list<Line*> lineList;

public:
	PolyLine(void);
	~PolyLine(void);

	void add(Line* line);
	void close();
	void draw();

};

#endif