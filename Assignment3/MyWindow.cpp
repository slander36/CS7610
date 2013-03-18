/*
 *	MyWindow.cpp
 *
 *	Created on : Jan 26, 2013
 *  Updated on : Feb 01, 2013
 *  Course     : CS4610/7610
 *  Instructor : Kannappan Palaniappan
 *	Author	   : Rui Wang
 *	Purpose    : Main drawing&viewing Window.
 *
 *
 *	Updated By : Sean Lander
 *	Updated On : Feb 03, 2013
 *
 *	Copyright University of Missouri-Columbia
 */


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Buffer.h>
#include <FL/gl.h>
#include "MyWindow.h"


const int MyWindow::CLEAR = 0;
const int MyWindow::LINE = 1;
const int MyWindow::CIRCLE = 2;
const int MyWindow::ELLIPSE = 3;
const int MyWindow::POLYLINE = 4;
const int MyWindow::POLYGON = 5;
const int MyWindow::RASTERIZE = 6;
const int MyWindow::FILLCIRCLE = 7;
const int MyWindow::SEMICIRCLE = 8;
const int MyWindow::RUBBERLINE = 9;
const int MyWindow::RUBBERCIRCLE = 10;
const int MyWindow::RUBBERPOLYLINE = 11;
const int MyWindow::DIALOGPOINT = 12;
const int MyWindow::DIALOGLINE = 13;
const int MyWindow::DIALOGCIRCLE = 14;
const int MyWindow::LINESAMPLE = 15;
const int MyWindow::LINEBOWTIE = 16;
const int MyWindow::LINEHOUSE = 17;
const int MyWindow::CIRCLESAMPLE = 18;
const int MyWindow::POLYGON1 = 19;
const int MyWindow::POLYGON2 = 20;
const int MyWindow::POLYGON3 = 21;
const int MyWindow::POLYGON4 = 22;
const int MyWindow::POLYGON5 = 23;
const int MyWindow::POLYGON6 = 24;
const int MyWindow::POLYGON7 = 25;
const int MyWindow::POLYGON8 = 26;
const int MyWindow::POLYGON9 = 27;

//---------------------------MyWindow::MyWindow--------------------------------
MyWindow::MyWindow(int x,int y,int width, int height, char* title) : Fl_Gl_Window(x,y,width, height, title) {
	mode(FL_RGB | FL_ALPHA | FL_DEPTH );

	swidth = width;
	sheight = height;
	shapeMode = 0;
	firsttime=0;
	clickCounter=0;

	currentLine = NULL;
	previousLine = NULL;
	
	polyline = NULL;
	polylineLine = NULL;

	currentCircle = NULL;
	previousCircle = NULL;

	startX = 0;
	startY = 0;
	finishX = 0;
	finishY = 0;
}


MyWindow::~MyWindow()
{}

//------------------------Mouse Callback Function------------------------------

void MyWindow::drawLine() {
	shapeMode = MyWindow::LINE;
	clickCounter = 0;
}

void MyWindow::drawCircle() {
	shapeMode = MyWindow::CIRCLE;
	clickCounter = 0;
}

void MyWindow::drawPolyline() {
	shapeMode = MyWindow::POLYLINE;
	clickCounter = 0;
}

void MyWindow::drawPolygon() {
	shapeMode = MyWindow::POLYGON;
	clickCounter = 0;
}

void MyWindow::drawPolygon1() {
	shapeMode = MyWindow::POLYGON1;
	redraw();
}

void MyWindow::drawPolygon2() {
	shapeMode = MyWindow::POLYGON2;
	redraw();
}

void MyWindow::drawPolygon3() {
	shapeMode = MyWindow::POLYGON3;
	redraw();
}

void MyWindow::drawPolygon4() {
	shapeMode = MyWindow::POLYGON4;
	redraw();
}

void MyWindow::drawPolygon5() {
	shapeMode = MyWindow::POLYGON5;
	redraw();
}

void MyWindow::drawPolygon6() {
	shapeMode = MyWindow::POLYGON6;
	redraw();
}

void MyWindow::drawPolygon7() {
	shapeMode = MyWindow::POLYGON7;
	redraw();
}

void MyWindow::drawPolygon8() {
	shapeMode = MyWindow::POLYGON8;
	redraw();
}

void MyWindow::drawPolygon9() {
	shapeMode = MyWindow::POLYGON9;
	redraw();
}

/*
 * Draw Samples with Lines
 */
void MyWindow::drawLineSample() {
	shapeMode = MyWindow::LINESAMPLE;
	redraw();
}

void MyWindow::drawLineBowtie() {
	shapeMode = MyWindow::LINEBOWTIE;
	redraw();
}

void MyWindow::drawLineHouse() {
	shapeMode = MyWindow::LINEHOUSE;
	redraw();
}

/*
 *	Draw Samples with Circles
 */

void MyWindow::drawCircleSample() {
	shapeMode = MyWindow::CIRCLESAMPLE;
	redraw();
}

void MyWindow::drawDialogStartingPoint() {
	shapeMode = MyWindow::DIALOGPOINT;
	redraw();
}
void MyWindow::drawDialogEndingPointLine() {
	shapeMode = MyWindow::DIALOGLINE;
	redraw();
}
void MyWindow::drawDialogCircle() {
	shapeMode = MyWindow::DIALOGCIRCLE;
	redraw();
}

/* Line Color */

void MyWindow::setColor() {
	rgba.red = widgetValueRed->value()/255;
	rgba.green = widgetValueGreen->value()/255;
	rgba.blue = widgetValueBlue->value()/255;
	rgba.alpha = 1;
}

void MyWindow::setColor(int colorIndex) {
	switch( colorIndex ) {
		case Colors::RED:
			widgetValueRed->value(255);
			widgetValueGreen->value(0);
			widgetValueBlue->value(0);
			break;
		case Colors::GREEN:
			widgetValueRed->value(0);
			widgetValueGreen->value(255);
			widgetValueBlue->value(0);
			break;
		case Colors::BLUE:
			widgetValueRed->value(0);
			widgetValueGreen->value(0);
			widgetValueBlue->value(255);
			break;
		case Colors::YELLOW:
			widgetValueRed->value(255);
			widgetValueGreen->value(255);
			widgetValueBlue->value(0);
			break;
		case Colors::CYAN:
			widgetValueRed->value(0);
			widgetValueGreen->value(255);
			widgetValueBlue->value(255);
			break;
		case Colors::MAGENTA:
			widgetValueRed->value(255);
			widgetValueGreen->value(0);
			widgetValueBlue->value(255);
			break;
		case Colors::CUSTOM:
			break;
		case Colors::WHITE:
		default:
			widgetValueRed->value(255);
			widgetValueGreen->value(255);
			widgetValueBlue->value(255);
	}
	setColor();
}

/* Line Pattern */

void MyWindow::setLineStyle(int lineStyleIndex) {
	switch(lineStyleIndex) {
		case LineStyle::DASHES:
			lineStyle = LineStyle::DASHES;
			break;
		case LineStyle::DOTS:
			lineStyle = LineStyle::DOTS;
			break;
		case LineStyle::MIXED:
			lineStyle = LineStyle::MIXED;
			break;
		case LineStyle::SOLID:
		default:
			lineStyle = LineStyle::SOLID;
	}
}

void MyWindow::updateThickness(int thickness) {
	lineThickness = thickness;
}

//-----------------------------------------------------------------------------

// ************************************************************************
//  This function initializes the GL prior to drawing anything 
// ************************************************************************
void MyWindow::InitializeGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);
	glColor3f(1.0,1.0,1.0);
	
	glShadeModel(GL_FLAT);
	
	glLoadIdentity();
	glViewport(0, 0, swidth, sheight);
    
	/* These variables specify the coordinate set to be used in glOrtho() */
	/* width() gives the width of the window */
	/* height() gives the height of the window */
	/* See QWidget documentation for more info */
	GLdouble left, right, high, down;
    
	left = - (float) swidth / 2;
	right = (float) swidth / 2;
	down = - (float) sheight / 2;
	high = (float) sheight / 2;
    
	glOrtho(left, right, down,high , -1, 1);
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLogicOp(GL_XOR);
	glDisable(GL_COLOR_LOGIC_OP);
}

//-----------------------------------------------------------------------------

// ************************************************************************
// Draws the widget. Never call this function directly. If needed, call
// redraw() instead.
// ************************************************************************

void MyWindow::draw() {
	if(firsttime==0) {
		InitializeGL();
		firsttime = 1;
	}
	//Switch between different drawing mode.
	int r;
	float polygon1[][2] = { {0, 30}, {10, 10}, {50, 10}, {80, 40}, {100, 40}, {110, 50}, {110, 115}, {130, 120}, {130, 130}, {100, 135}, {130, 140}, {130, 150}, {110, 160}, {80, 160}, {70, 150}, {70, 130}, {80, 120}, {70, 110}, {60, 60}, {40, 30}, {30, 20}, {10, 20} };
	float polygon2[][2] = { {80, 100}, {90, 90}, {100, 90}, {130, 80}, {140, 90}, {160, 90}, {150, 95}, {160, 100}, {150, 100}, {155, 110}, {145, 100}, {140, 110}, {140, 100}, {130, 90}, {110, 110}, {90, 110} };
	float polygon3[][2] = { {80, 60}, {80, 40}, {90, 30}, {90, 20}, {80, 10}, {80, 5}, {90, 0}, {120, 0}, {100, 10}, {100, 20}, {120, 40}, {110, 60}, {100, 70}, {90, 70} };
	float polygon4[][2] = { {87.5, 150}, {90, 147}, {96, 147}, {101, 150}, {96, 152.5}, {90, 152.5} };
	float polygon5[][2] = { {125.0,275.0}, {375.0,275.0}, { 150.0,  150.0}, {250.0, 350.0}, {350.0,  150.0} };
	float polygon6[][2] = { {9*4,5*4}, {14*4,5*4}, {14*4,11*4}, {22*4,11*4}, {27*4,16*4}, {20*4,25*4}, {13*4,25*4}, {13*4,20*4}, {8*4,20*4}, {8*4,16*4}, {4*4,16*4}, {4*4,9*4} };
	float polygon7[][2] = { {2,3}, {7,1}, {13,5}, {13,11}, {7,7}, {2,9} };
	float polygon8[][2] = { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10},{25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20},{15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };
	float polygon9[][2] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30}};
	switch(shapeMode) {
		case MyWindow::LINE:
			if(clickCounter == 0) {
				currentLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				currentLine->draw();
				if(previousLine) delete previousLine;
				previousLine = currentLine;
			} else if(clickCounter == 1) {
				//Draw first point
				glBegin(GL_POINTS);
				glVertex2i(startX, startY);
				glEnd();
			} else if(clickCounter == 2) {
				// Rubber Band Mode
				// Redraw Old Line
				if(previousLine) previousLine->draw();
				// Create New Line and Draw
				currentLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				currentLine->draw();
				// Free Memory and Swap Pointers
				delete previousLine;
				previousLine = currentLine;
			}
			break;
            
		case MyWindow::DIALOGPOINT:
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex2i(round(dialogStartX), round(dialogStartY));
			glEnd();
			glPointSize(1.0);
			break;
            
		case MyWindow::DIALOGLINE:
			glPointSize(5.0);
			glBegin(GL_POINTS);
			glVertex2i(round(dialogStartX), round(dialogStartY));
			glVertex2i(round(dialogEndX), round(dialogEndY));
			glEnd();
			glPointSize(1.0);
			currentLine = new Line(round(dialogStartX), round(dialogStartY), round(dialogEndX), round(dialogEndY));
			currentLine->setLineStyle(lineStyle);
			currentLine->setLineThickness(lineThickness);
			currentLine->setColor(rgba);
			currentLine->setTextDisplay(textDisplay);
			currentLine->setPrint(print);
			currentLine->draw();
			delete currentLine;
			break;

		case MyWindow::DIALOGCIRCLE:
			currentCircle = new Circle(dialogCircleX, dialogCircleY, dialogCircleR, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			
		case MyWindow::CIRCLE:
			if(clickCounter == 0) {
				r = round(sqrt(1.0*(startX-finishX)*(startX-finishX) + 1.0*(startY-finishY)*(startY-finishY)));
				currentCircle = new Circle(startX, startY, r, lineThickness, lineStyle, textDisplay, print, rgba);
				currentCircle->draw();
				if(previousCircle) delete previousCircle;
				previousCircle = currentCircle;
			} else if(clickCounter == 1) {
				// Draw Center Point
				glBegin(GL_POINTS);
				glVertex2i(startX, startY);
				glEnd();
			} else if(clickCounter == 2) {
				// Rubber Band Mode
				// Redraw Old Circle
				if(previousCircle) previousCircle->draw();
				// Create and Draw New Circle
				r = round(sqrt(1.0*(startX-finishX)*(startX-finishX) + 1.0*(startY-finishY)*(startY-finishY)));
				currentCircle = new Circle(startX, startY, r, lineThickness, lineStyle, textDisplay, print, rgba);
				currentCircle->draw();
				// Free Memory and Swap Pointers
				delete previousCircle;
				previousCircle = currentCircle;
			}
			break;
            
		case MyWindow::POLYLINE:
			if(clickCounter == 1) {
				// Create a new line and add it to the polyline
				polylineLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				polyline->add(polylineLine);
			} else if(clickCounter == 2) {
				// Draw the final line and reset
				// Done with MIDDLE MOUSE
				polylineLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				polyline->add(polylineLine);
				clickCounter = 0;
				delete polyline;
			} else if(clickCounter == 3) {
				// Close for polygon
				// Done with RIGHT MOUSE
				polyline->close();
				clickCounter = 0;
				delete polyline;
			} else {
				//Draw first point
				glBegin(GL_POINTS);
				glVertex2i(startX, startY);
				glEnd();
				clickCounter = 1;
			}
			break;
            
		case MyWindow::POLYGON:
			if(clickCounter == 1) {
				// Create a new line and add it to the polyline
				polygonLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				polygon->add(polygonLine);
			} else if(clickCounter == 2) {
				// Draw the final line and reset
				// Done with MIDDLE MOUSE
				// DO NOTHING - NOT A POLYLINE
				/*
				polygonLine = new Line(startX, startY, finishX, finishY, lineThickness, lineStyle, textDisplay, print, rgba);
				polygon->add(polygonLine);
				clickCounter = 0;
				delete polygon;
				*/
			} else if(clickCounter == 3) {
				// Close for polygon
				// Done with RIGHT MOUSE
				polygon->close();
				polygon->draw();
				clickCounter = 0;
				delete polygon;
			} else {
				//Draw first point
				glBegin(GL_POINTS);
				glVertex2i(startX, startY);
				glEnd();
				clickCounter = 1;
			}
			break;

		case MyWindow::LINESAMPLE:
			currentLine = new Line(10, -10, -10, 10, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(-2, 8, 8, 8, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(8, 8, -2, 8, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(0, -7, 0, 5, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(3.2, -9.6, 16.7, 5.9, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(16.6, 5.8, 3.2, -9.7, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(1, 1, 1, 1, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(-1, 0, 1, 10, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(1, 0, -1, 10, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(-1, 1, 10, -1, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(-1, -1, 10, 1, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			break;

		case MyWindow::LINEBOWTIE:
			currentLine = new Line(100, 100, 100, 60, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(100, 60, 120, 76, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(120, 76, 140, 60, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(140, 60, 140, 100, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(140, 100, 120, 84, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(120, 84, 100, 100, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			break;

		case MyWindow::LINEHOUSE:
			currentLine = new Line(40, 40, 40, 90, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(40, 90, 70, 120, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(70, 120, 100, 90, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(100, 90, 100, 40, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(100, 40, 40, 40, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(50, 100, 50, 120, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(50, 120, 60, 120, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(60, 120, 60, 110, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(50, 40, 60, 75, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(60, 75, 70, 40, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(80, 75, 90, 75, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(90, 75, 85, 90, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			currentLine = new Line(85, 90, 80, 75, lineThickness, lineStyle, textDisplay, print, rgba);
			currentLine->draw();
			delete currentLine;
			break;

		case MyWindow::CIRCLESAMPLE:
			currentCircle = new Circle(0, 0, 10, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			currentCircle = new Circle(7, 7, 7, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			currentCircle = new Circle(-9, 3, 13, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			currentCircle = new Circle(-7.4, -2.5, 11.4, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			currentCircle = new Circle(6, -3, 12, lineThickness, lineStyle, textDisplay, print, rgba);
			currentCircle->draw();
			delete currentCircle;
			break;

		case MyWindow::POLYGON1:
			polygon = new sldraw::Polygon(new Colors::rgba(0.0,0.5,0.0,1.0), printSET, printAET, textDisplay);
			for(int i = 0 ; i < 21 ; i++) {
				currentLine = new Line(polygon1[i][0],polygon1[i][1],polygon1[i+1][0],polygon1[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON2:
			polygon = new sldraw::Polygon(new Colors::rgba(1.0,1.0,0.0,1.0), printSET, printAET, textDisplay);
			for(int i = 0 ; i < 15 ; i++) {
				currentLine = new Line(polygon2[i][0],polygon2[i][1],polygon2[i+1][0],polygon2[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON3:
			polygon = new sldraw::Polygon(new Colors::rgba(0.67,0.31,0.0,1.0), printSET, printAET, textDisplay);
			for(int i = 0 ; i < 13 ; i++) {
				currentLine = new Line(polygon3[i][0],polygon3[i][1],polygon3[i+1][0],polygon3[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON4:
			polygon = new sldraw::Polygon(new Colors::rgba(1.0,0.0,0.0,1.0), printSET, printAET, textDisplay);
			for(int i = 0 ; i < 5 ; i++) {
				currentLine = new Line(polygon4[i][0],polygon4[i][1],polygon4[i+1][0],polygon4[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON5:
			polygon = new sldraw::Polygon(new Colors::rgba(1.0,1.0,1.0,1.0), printSET, printAET, textDisplay);
			for(int i = 0 ; i < 4 ; i++) {
				currentLine = new Line(polygon5[i][0],polygon5[i][1],polygon5[i+1][0],polygon5[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON6:
			polygon = new sldraw::Polygon(true, printSET, printAET, textDisplay);
			for(int i = 0 ; i < 11 ; i++) {
				currentLine = new Line(polygon6[i][0],polygon6[i][1],polygon6[i+1][0],polygon6[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON7:
			polygon = new sldraw::Polygon(true, printSET, printAET, textDisplay);
			for(int i = 0 ; i < 5 ; i++) {
				currentLine = new Line(polygon7[i][0],polygon7[i][1],polygon7[i+1][0],polygon7[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON8:
			polygon = new sldraw::Polygon(true, printSET, printAET, textDisplay);
			for(int i = 0 ; i < 17 ; i++) {
				currentLine = new Line(polygon8[i][0],polygon8[i][1],polygon8[i+1][0],polygon8[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;

		case MyWindow::POLYGON9:
			polygon = new sldraw::Polygon(true, printSET, printAET, textDisplay);
			for(int i = 0 ; i < 14 ; i++) {
				currentLine = new Line(polygon9[i][0],polygon9[i][1],polygon9[i+1][0],polygon9[i+1][1]);
				polygon->add(currentLine);
			}
			polygon->close();
			polygon->draw();
			break;
	}
}

//-----------------------------------------------------------------------------

// ************************************************************************
// Handle events(eg. mouse, keyboard) in your program or widget
// ************************************************************************

int MyWindow::handle(int event) {
	switch (event) {
		case FL_PUSH:
			switch(Fl::event_button()) {
				case FL_LEFT_MOUSE:
					switch(shapeMode) {
						case MyWindow::LINE:
							if(clickCounter == 0) {
								startX = Fl::event_x() - swidth/2;		//Get the X mouse position
								startY = sheight/2 - Fl::event_y();		//Get the Y mouse position
							}
							else if(clickCounter == 1) {
								finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord 
								finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
							}
							clickCounter = (clickCounter + 1) % 2;
							redraw();
							return 1;
                    
						case MyWindow::CIRCLE:
							if(clickCounter == 0) {
								startX = Fl::event_x() - swidth/2;		//Get the X mouse position
								startY = sheight/2 - Fl::event_y();		//Get the Y mouse position
							}
							else if(clickCounter == 1) {
								finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
								finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
							}
							clickCounter = (clickCounter + 1) % 2;
							redraw();
							return 1;
                    
						case MyWindow::POLYLINE:
							if(clickCounter == 0) {
								polyline = new PolyLine();
								finishX = Fl::event_x() - swidth/2;		//Get the X mouse position
								finishY = sheight/2 - Fl::event_y();		//Get the Y mouse position
								startX = finishX;
								startY = finishY;
							} else {
								startX = finishX;
								startY = finishY;
								finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
								finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
							}
							redraw();
							return 1;
                    
						case MyWindow::POLYGON:
							if(clickCounter == 0) {
								polygon = new sldraw::Polygon(true, printSET, printAET, textDisplay);
								finishX = Fl::event_x() - swidth/2;		//Get the X mouse position
								finishY = sheight/2 - Fl::event_y();		//Get the Y mouse position
								startX = finishX;
								startY = finishY;
							} else {
								startX = finishX;
								startY = finishY;
								finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
								finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
							}
							redraw();
							return 1;
					}
				break;

				case FL_MIDDLE_MOUSE:
					switch(shapeMode) {
						case MyWindow::POLYLINE:
							startX = finishX;
							startY = finishY;
							finishX = Fl::event_x() - swidth/2;			//Get end point of line X coord
							finishY = sheight/2 - Fl::event_y();		//Get end point of line Y coord
							clickCounter = 2;
							redraw();
							return 1;
					}
					break;

				case FL_RIGHT_MOUSE:
					switch(shapeMode) {
					case MyWindow::POLYLINE:
						clickCounter = 3;
						redraw();
						return 1;
					case MyWindow::POLYGON:
						clickCounter = 3;
						redraw();
						return 1;
					}
					break;
			}
			break;

		case FL_DRAG:
			switch(shapeMode) {
				case MyWindow::LINE:
					if(clickCounter == 0) {
						glEnable(GL_COLOR_LOGIC_OP);
						clickCounter = 2;
					}
					else if(clickCounter == 1) {
						clickCounter = 0;
						finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
						finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
						redraw();
					}
					if(clickCounter == 2) {
						finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
						finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
						redraw();
					}
					return 1;

				case MyWindow::CIRCLE:
					if(clickCounter == 0) {
						glEnable(GL_COLOR_LOGIC_OP);
						clickCounter = 2;
					}
					if(clickCounter == 1) {
						clickCounter = 0;
					}
					finishX = Fl::event_x() - swidth/2;		//Get end point of line X coord
					finishY = sheight/2 - Fl::event_y();	//Get end point of line Y coord
					redraw();
					return 1;
			}
			break;

		case FL_RELEASE:
			switch(shapeMode) {
			case MyWindow::LINE:
				if(clickCounter != 1) {
					glDisable(GL_COLOR_LOGIC_OP);
					clickCounter = 0;
					redraw();
				}
				return 1;

			case MyWindow::CIRCLE:
				if(clickCounter != 1) {
					glDisable(GL_COLOR_LOGIC_OP);
					clickCounter = 0;
					redraw();
				}
				return 1;
			}
			break;
	}
	return Fl_Gl_Window::handle(event);
}

//-----------------------------------------------------------------------------

// ************************************************************************
// Clean the window and clear all the variables
// ************************************************************************

void MyWindow::clearallvariables() {
	shapeMode = MyWindow::CLEAR;
	clickCounter = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	redraw();
}


