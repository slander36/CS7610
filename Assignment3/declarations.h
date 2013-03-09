/*
 * Author: Sean Lander
 * Date: Feb. 05, 2013
 * Description:
 *  Collection of enums and structs
 *	useful in graphics programming
 */

#pragma once
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <cmath>
#include <FL/Fl_Text_Display.h>

namespace LineStyle {
	enum Style {
		SOLID,
		DASHES,
		DOTS,
		MIXED,
		MAX_STYLES
	};

	typedef struct DRAWMASK {
		int* drawMask;
		int drawMaskSize;
		DRAWMASK() : drawMask((int*)NULL), drawMaskSize(0) { };
		DRAWMASK(int* n_drawMask, int n_drawMaskSize) :
			drawMask(n_drawMask), drawMaskSize(n_drawMaskSize)
		{ };
	} DrawMask;

	inline DrawMask* getDrawMask(Style lineStyle) {
		int* drawMask;
		int drawMaskSize;
		switch(lineStyle) {
		case LineStyle::DASHES:
			drawMaskSize = 8;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1; drawMask[2] = 1; drawMask[3] = 1;
			drawMask[4] = 0; drawMask[5] = 0; drawMask[6] = 0; drawMask[7] = 0;
			break;
		case LineStyle::DOTS:
			drawMaskSize = 4;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1;
			drawMask[2] = 0; drawMask[3] = 0;
			break;
		case LineStyle::MIXED:
			drawMaskSize = 10;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1; drawMask[1] = 1; drawMask[2] = 1; drawMask[3] = 1;
			drawMask[4] = 0; drawMask[5] = 0;
			drawMask[6] = 1; drawMask[7] = 1;
			drawMask[8] = 0; drawMask[9] = 0;
			break;
		case LineStyle::SOLID:
		default:
			drawMaskSize = 1;
			drawMask = (int*)malloc(drawMaskSize * sizeof(drawMask));
			drawMask[0] = 1;
		}

		DrawMask* p_DrawMask = new DrawMask(drawMask, drawMaskSize);

		return p_DrawMask;
	}
}

namespace Colors {
	enum Color {
		WHITE,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA,
		CUSTOM,
		MAX_COLORS
	};

	typedef struct RGBA {
		float red;
		float green;
		float blue;
		float alpha;
		RGBA() : red(1), green(1), blue(1), alpha(1) { };
		RGBA( float r, float g, float b, float a ) :
			red(r), green(g), blue(b), alpha(a)
		{ };
	} rgba;

	const rgba ColorArray[MAX_COLORS] = {
		*(new rgba(1,1,1,1)),
		*(new rgba(1,0,0,1)),
		*(new rgba(0,1,0,1)),
		*(new rgba(0,0,1,1)),
		*(new rgba(1,1,0,1)),
		*(new rgba(0,1,1,1)),
		*(new rgba(1,0,1,1)),
		*(new rgba(1,1,1,1))
	};
}

inline int round(float x) { return (int)(floor(x+0.5)); };

#endif
