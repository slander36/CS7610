# /*
# *Makefile
# *
# *	Created on : Jan 26, 2013
# * Course     : CS4610/7610
# * Instructor : Kannappan Palaniappan
# *	Author	   : Rui Wang
# *	Purpose    : Building your program executable
# *
# *	Copyright University of Missouri-Columbia
# */

CXX      = $(shell fltk-config --cxx)
DEBUG    =-g3
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags ) -I.
LDFLAGS  = $(shell fltk-config --use-gl --use-images --ldflags )
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags )
LINK     = $(CXX)

TARGET = linedraw_test

OBJS = main.o ui.o MyWindow.o DrawingAlgorithm.o Object.o Line.o Shape.o PolyLine.o Circle.o
SRCS = main.cpp ui.cpp MyWindow.cpp DrawingAlgorithm.cpp Object.cpp Line.cpp Shape.cpp PolyLine.cpp Circle.cpp

.SUFFIXES: .o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

debug: $(TARGET)
	$(LINK) $(DEBUG) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
main.o: main.cpp
ui.o: ui.cxx ui.h
MyWindow.o: MyWindow.cpp MyWindow.h
DrawingAlgorithm.o: DrawingAlgorithm.cpp DrawingAlgorithm.h
Object.o: Object.cpp Object.h
Line.o: Line.cpp Line.h
Shape.o: Shape.cpp Shape.h
PolyLine.o: PolyLine.cpp PolyLine.h
Circle.o: Circle.cpp Circle.h

clean: $(TARGET) $(OBJS)
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null
