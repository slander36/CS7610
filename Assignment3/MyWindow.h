/*
 *	MyWindow.h
 *
 *	Created on : Jan 26, 2013
 *  Updated on : Feb 01, 2013
 *  Course     : CS4610/7610
 *  Instructor : Kannappan Palaniappan
 *	Author	   : Rui Wang
 *	Purpose    : Class definition for main drawing&viewing window 
 *
 *
 *	Updated By : Sean Lander
 *	Updated On : Feb 03, 2013
 *
 *	Copyright University of Missouri-Columbia
 */

#pragma once
#ifndef MY_WINDOW_H
#define MY_WINDOW_H
//#include "DrawingAlgorithm.h"
#include <FL/Fl_Gl_Window.h>
#include <FL/Fl_Text_Display.h>
#include <FL/Fl_Value_Input.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Line.h"
#include "Circle.h"
#include "PolyLine.h"
#include "Polygon.h"

class MyWindow : public Fl_Gl_Window
{
	private:
		// Lines
		Line *currentLine;
		Line *previousLine;

		// Polylines/Polygons
		PolyLine *polyline;
		sldraw::Polygon *polygon;
		Line *polylineLine;
		Line *polygonLine;

		// Circles
		Circle *currentCircle;
		Circle *previousCircle;
  public:
      MyWindow(int x,int y,int width, int height, char* title);
      virtual ~MyWindow();
      void InitializeGL();
      virtual void draw();
	  
	/*<<<<<<<<<<<<<<<<<<<<<drawMouseLine>>>>>>>>>>>>>>>>>>>>>
	 Enables interactive line drawing
	 */
	void drawLine();

	/*
	 * Draw Samples with Lines
	 */
	void drawLineSample();
	void drawLineBowtie();
	void drawLineHouse();
	
	/*<<<<<<<<<<<<<<<<<<<<<drawMouseCircle>>>>>>>>>>>>>>>>>>>
	Enables interactive circle drawing
	*/
	void drawCircle();

	/*
	 *	Draw Samples with Circles
	 */
	void drawCircleSample();
	
	/*<<<<<<<<<<<<<<<<<<<<<drawMousePolyline>>>>>>>>>>>>>>>>>
	 Enables interactive polyline drawing
	*/
	void drawPolyline();

	/*
	 * Polygon
	 */
	void drawPolygon();
	void drawPolygon1();
	void drawPolygon2();
	void drawPolygon3();
	void drawPolygon4();
	void drawPolygon5();
	void drawPolygon6();
	void drawPolygon7();
	void drawPolygon8();
	void drawPolygon9();

	/*
	 * Set Line Color
	 */

	Fl_Value_Input * widgetValueRed;
	Fl_Value_Input * widgetValueGreen;
	Fl_Value_Input * widgetValueBlue;
	float colorValueRed;
	float colorValueGreen;
	float colorValueBlue;
	Colors::rgba rgba;

	void setColor();
	void setColor(int colorIndex);

	/*
	 * Set Line Thickness
	 */

	int lineThickness;
	
	void updateThickness(int thickness);
  
	/*
	 * Set Line Pattern
	 */

	LineStyle::Style lineStyle;

	void setLineStyle(int lineStyleIndex);
	 
	/*<<<<<<<<<<<<<<<<<<<<<drawMouseDialogPoint>>>>>>>>>>>>>>
	Enables interactive dialogpoint drawing
	*/
	void drawDialogStartingPoint();
	void drawDialogEndingPointLine();

	void drawDialogCircle();
    
	/*<<<<<<<<<<<<<<<<<<<<ClearShapeVariables>>>>>>>>>>>>>>>>
	*/
	void clearallvariables();
	
	// handles the keyboard and mouse input
	virtual int handle(int event);
    
	 
	//Set of static variables to represent the shapes 
	static const int CLEAR;
	static const int LINE;
	static const int CIRCLE;
	static const int ELLIPSE;
	static const int POLYLINE;
	static const int POLYGON;
	static const int RASTERIZE;
	static const int FILLCIRCLE;
	static const int SEMICIRCLE;
	static const int RUBBERLINE;
	static const int RUBBERCIRCLE;
	static const int RUBBERPOLYLINE;
	static const int DIALOGPOINT;
	static const int DIALOGLINE;
	static const int DIALOGCIRCLE;
	static const int LINESAMPLE;
	static const int LINEBOWTIE;
	static const int LINEHOUSE;
	static const int CIRCLESAMPLE;
	static const int POLYGON1;
	static const int POLYGON2;
	static const int POLYGON3;
	static const int POLYGON4;
	static const int POLYGON5;
	static const int POLYGON6;
	static const int POLYGON7;
	static const int POLYGON8;
	static const int POLYGON9;
	
	//screen size
	int swidth;
	int sheight;
	
	//mouse click counter
	int clickCounter;
	
	//line start and end point
	int startX, startY ,finishX, finishY;
    
	//dialog points
	float dialogStartX,dialogStartY,dialogEndX,dialogEndY;

	// Dialog Values for Circle
	float dialogCircleX, dialogCircleY, dialogCircleR;

	//print variables
	Fl_Text_Display * textDisplay;
	bool print;
	
	//Initialization
	int firsttime;
	
private:
	//The current shape being drawn (line, circle or ellipse)
	int shapeMode;
};

#endif
