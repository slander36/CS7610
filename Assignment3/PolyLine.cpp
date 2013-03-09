#include "PolyLine.h"


PolyLine::PolyLine(void)
{
}


PolyLine::~PolyLine(void)
{
}

void PolyLine::add(Line* line) {
	line->draw();
	lineList.push_back(line);
}

void PolyLine::close() {
	int xe = lineList.front()->getxs();
	int ye = lineList.front()->getys();
	int xs = lineList.back()->getxe();
	int ys = lineList.back()->getye();
	float lineThickness = lineList.back()->getLineThickness();
	LineStyle::Style style = lineList.back()->getLineStyle();
	Fl_Text_Display* textDisplay = lineList.back()->getTextDisplay();
	bool print = lineList.back()->getPrint();
	Colors::rgba rgba = lineList.back()->getColor();

	Line* line = new Line(xs, ys, xe, ye, lineThickness, style, textDisplay, print, rgba);
	line->draw();
	lineList.push_back(line);
}

void PolyLine::draw() {
	std::list<Line*>::iterator it = lineList.begin();
	for(; it!=lineList.end() ; ++it) {
		(*it)->draw();
	}
}
