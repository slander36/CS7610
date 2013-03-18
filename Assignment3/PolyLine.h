#pragma once
#ifndef _SL_POLYLINE
#define _SL_POLYLINE

#include "Shape.h"
#include "Line.h"
#include <list>
#include <vector>

class PolyLine : public Shape {

protected:
	std::list<Line*> lineList;

public:
	PolyLine(void);
	~PolyLine(void);

	virtual void add(Line* line);
	virtual void close();
	virtual void draw();

};

#endif