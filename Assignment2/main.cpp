/*
 *	Main.cpp
 *
 *	Created on : Jan 26, 2013
 *  Course     : CS4610/7610
 *  Instructor : Kannappan Palaniappan
 *	Author	   : Rui Wang
 *	Purpose    : Driver user interface startup for sample Assignment 1
 *
 *	Copyright University of Missouri-Columbia
 */

#include "MyWindow.h"
#include "ui.h"
#include <FL/FL.H>


//=============================================================================
// Sample Program for CS4610 first assignment
//=============================================================================


int main(int argc, char** args)
{
    //Create a user defined window object
    UserInterface m;
	m.show();
	
	Fl::run();
	
	return 0;
}
//-----------------------------------------------------------------------------

