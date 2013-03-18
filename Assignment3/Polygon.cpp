#include "Polygon.h"

namespace Edge {
	typedef struct edge {
		int ymax;
		int xwhole, xfraction;
		int dx;
		int dy;
		float cR, cG, cB, cA;
		float uR, uG, uB, uA;
		struct edge *nextEdge;
		struct edge(int _ymax, int _xwhole, int _xfraction, int _dx, int _dy,
			float _cR, float _cG, float _cB, float _cA,
			float _uR, float _uG, float _uB, float _uA) :
				ymax(_ymax), xwhole(_xwhole), xfraction(_xfraction), dx(_dx), dy(_dy),
				cR(_cR), cG(_cG), cB(_cB), cA(_cA),
				uR(_uR), uG(_uG), uB(_uB), uA(_uA),
				nextEdge(NULL)
				{ };
	} Edge;

	bool compare_edge(Edge* e_one, Edge* e_two) {
		if(e_one->xwhole == e_two->xwhole) {
			return (e_one->xfraction > e_two->xfraction);
		}
		return (e_one->xwhole > e_two->xwhole);
	};
}

namespace sldraw {

	Polygon::~Polygon(void)
	{
	}

	void Polygon::add(Line* line) {
		//line->draw();
		lineList.push_back(line);
	}

	void Polygon::close() {
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
		//line->draw();
		lineList.push_back(line);
	}

	void Polygon::draw() {
		/* Scanline Fill with Goraud Shading
		 *	1. Create Sorted Edge Table on Y from lineList
		 *	2. Loop until AET and SET are empty
		 *		1. Pop from SET, push to AET on Y
		 *		2. Drop from AET on Y
		 *		3. Sort AET on X
		 *		4. Updated cR, cG, cB for AET edges
		 *		5. Draw using Even-Odd (should use Goraud Shading
		 *		6. Update Y
		 *	3. Redraw edges using selected border color
		 */
		
		glBegin(GL_POINTS);

		// Initialize for use in creating the SET
		Line *line; // current line
		int ymax, ymin, xmax, xmin; // line information for edges
		int xwhole; // current x value of edge
		int xfraction = 0; // current fraction of x whole value
		int dx; // change in xfraction every time y is increased
		int dy; // number to compare xfraction to at each interval
		float cR, cG, cB, cA; // current RGBA value
		float tempR, tempG, tempB; // temporary RGBA value
		float uR, uG, uB, uA; // update RGBA value
		const int numEdges = lineList.size();
		std::map<int,Edge::Edge *> set; // Sorted Edge Table
		std::list<Edge::Edge *> aet; // Active Edge Table
		Edge::Edge *edge; // current edge

		// Initialize Color to Red
		cR = 1; cG = 0; cB = 0; cA = 1;
		tempR = 0; tempG = 1; tempB = 0;
		uR = 0; uG = 0; uB = 0; uA = 0;

		// Data for aet
		int ylowest=10000;
		int ygreatest=0;

		std::list<Line*>::iterator it = lineList.begin();
		for(; it!=lineList.end() ; ++it) {
			line = (*it);
			if( line->getye() == line->getys() ) {
				continue;
			} else if( line->getye() > line->getys() ) {
				ymax = line->getye();
				ymin = line->getys();
				xmax = line->getxe();
				xmin = line->getxs();
			} else {
				ymax = line->getys();
				ymin = line->getye();
				xmax = line->getxs();
				xmin = line->getxe();
			}
			xwhole = xmin;
			xfraction = 0;
			dy = ymax - ymin;
			dx = xmax - xmin;
			if( randomFill && line->getye() > line->getys()) {
				float tempG = cR;
				float tempB = cG;
				float tempR = cB;
				uR = (cR - tempR)/dy;
				uG = (cG - tempG)/dy;
				uB = (cB - tempB)/dy;
				cR = tempR;
				cG = tempG;
				cB = tempB;
			} else if( randomFill && line->getys() > line->getye()) {
				float tempB = cR;
				float tempR = cG;
				float tempG = cB;
				uR = (cG - tempR)/dy;
				uG = (cB - tempG)/dy;
				uB = (cR - tempB)/dy;
				cR = tempR;
				cG = tempG;
				cB = tempB;
			} else if( fill != NULL ) {
				cR = fill->red;
				uR = fill->red;
				cG = fill->green;
				uG = fill->green;
				cB = fill->blue;
				uB = fill->blue;
				cA = fill->alpha;
				uA = fill->alpha;
			}
			// Create Edge
			edge = new Edge::Edge(ymax, xwhole, xfraction, dx, dy, cR, cG, cB, cA, uR, uG, uB, uA);
			// Add edge to current edge list
			if(set.count(ymin) > 0) {
				Edge::Edge *tempEdge = set[ymin];
				while(tempEdge->nextEdge != NULL) {
					tempEdge = tempEdge->nextEdge;
				}
				tempEdge->nextEdge = edge;
			} else {
				// If no edges exist at this y, add it on
				set[ymin] = edge;
			}
			ygreatest = (ygreatest > ymax ? ygreatest : ymax);
			ylowest = (ylowest < ymin ? ylowest : ymin);
		}

		int y = ylowest;
		while(!set.empty() || !aet.empty()) {
			// 1. ADD edges from set to aet
			if(set.count(y)>0) {
				Edge::Edge *tempEdge = set[y];
				while(tempEdge != NULL) {
					std::cout << "Adding edge (" << tempEdge->ymax << "," << tempEdge->xwhole << "," << tempEdge->dx << "," << tempEdge->dy << ") at y=" << y << std::endl;
					aet.push_front(tempEdge);
					tempEdge = tempEdge->nextEdge;
				}
				set.erase(y);
			}
			// 2. REMOVE existing edges from aet
			std::list<Edge::Edge*>::iterator it = aet.begin();
			for(; it != aet.end() ; ++it) {
				if((*it)->ymax <= y) aet.remove(*it);
			}
			// 3. SORT aet on x-coord
			aet.sort(Edge::compare_edge);
			// If for some reason aet is not a multiple of two, die
			if((aet.size()%2) != 0) {
				std::cout << aet.size() << std::endl;
				Sleep(10000);
				exit(-1);
			}
			// 4. FILL between pairs of x-coords from aet
			it = aet.begin();
			Edge::Edge* e1, * e2;
			// Skipping alpha for now
			// TODO: Add alpha back in for some reason?
			float r1, r2, g1, g2, b1, b2, ur, ug, ub;
			for(; it != aet.end() ; ++it) {
				// Grab the first edge
				e1 = *it;
				r1 = e1->cR;
				g1 = e1->cG;
				b1 = e1->cB;
				// Then the second one
				it++;
				e2 = *it;
				r2 = e2->cR;
				g2 = e2->cG;
				b2 = e2->cB;
				// Calculate the update rate
				int diffx = e2->xwhole - e1->xwhole;
				ur = (r2-r1)/diffx;
				ug = (g2-g1)/diffx;
				ub = (b2-b1)/diffx;
				for( int x = e1->xwhole ; x <= e2->xwhole ; ++x ) {
					glColor3f(r1,g1,b1);
					glVertex2i(x,y);
					r1 += ur;
					g1 += ug;
					b1 += ub;
				}
			}
			// 5. INCREMENT y and UPDATE x-coord
			y++;
			it = aet.begin();
			Edge::Edge *temp;
			for(; it != aet.end() ; ++it) {
				temp= *it;
				temp->xfraction += abs(temp->dx);
				// +dx < +dy
				if(temp->dx >= 0) {
					if(temp->dy > temp->dx) {
						if(temp->xfraction > temp->dy) {
							temp->xwhole++;
							temp->xfraction = temp->xfraction%temp->dy;
						}
					} else {
						temp->xwhole += temp->xfraction/temp->dy;
						temp->xfraction = temp->xfraction%temp->dy;
					}
				} else {
					if(temp->dy > abs(temp->dx)) {
						if(temp->xfraction > temp->dy) {
							temp->xwhole--;
							temp->xfraction = temp->xfraction%temp->dy;
						}
					} else {
						temp->xwhole -= temp->xfraction/temp->dy;
						temp->xfraction = temp->xfraction%temp->dy;
					}
				}
			}
		}

		// Draw the border
		it = lineList.begin();
		for(; it != lineList.end() ; ++it) {
			(*it)->draw();
		}

		glEnd();
	}
}