#include "Circle.h"

void Circle::draw() {
	/* Prepare OpenGL */

	// Set Line Thickness
	glPointSize(getLineThickness());

	// Set Draw Color
	glColor4f(rgba.red, rgba.green, rgba.blue, rgba.alpha);

	// Tell OpenGL What to draw
	glBegin(GL_POINTS);

	/* OpenGL Ready. Draw Circle */

	/* Circle Drawing Algorithm */

	// Initialize variables
	int xo = 0;
	int yo = getR();
	int p = 1 - getR();
	int step = 0;

	setPixel(xo, yo, step);

	/* While xo is less than yo, meaning the angle is still steeper than 45 */
	while(xo < yo) {
		step++;
		if(p < 0) { /* E Pixel Chosen */
			p += (xo<<1) + 3;
			xo++;
		} else { /* SE Pixel Chosen */
			p += (xo<<1) - (yo<<1) + 5;
			xo++;
			yo--;
		}
		setPixel(xo, yo, step);
	}

	/* End Circle Draw Algorithm */

	// Reset OpenGL
	glEnd();

	glColor4f(1.0,1.0,1.0,1.0);

	glPointSize(1.0);

}

/* Used to draw the 8 points of a circle */
void Circle::setPixel(int xo, int yo, int step) {
	/* Print Information */
	std::stringstream ostream;
	Fl_Text_Buffer * textBuffer = NULL;
	if( print ) {
		textBuffer = textDisplay->buffer();
	}

	int X = x+xo;
	int Y = y+yo;

	ostream << "Step " << step << " (calculated):\n";

	/* First Quadrant Clockwise */
	glVertex2i(X, Y);
	if(print) ostream << "(" << X << "," << Y << ")\n";
	Y = y-yo;
	glVertex2i(X, Y);
	if(print) ostream << "(" << X << "," << Y << ")\n";
	if( xo != 0 ) {
		X = x-xo;
		glVertex2i(X, Y);
		if(print) ostream << "(" << X << "," << Y << ")\n";
		Y = y+yo;
		glVertex2i(X, Y);
		if(print) ostream << "(" << X << "," << Y << ")\n";
	}
	
	Y = y+xo;
	X = x+yo;
	glVertex2i(X, Y);
	if(print) ostream << "(" << X << "," << Y << ")\n";
	X = x-yo;
	glVertex2i(X, Y);
	if(print) ostream << "(" << X << "," << Y << ")\n";
	if( xo != 0 ) {
		Y = y-xo;
		glVertex2i(X, Y);
		if(print) ostream << "(" << X << "," << Y << ")\n";
		X = x+yo;
		glVertex2i(X, Y);
		if(print) ostream << "(" << X << "," << Y << ")\n";
	}

	if(print) textBuffer->append(ostream.str().c_str());

}