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
			return (e_one->xfraction < e_two->xfraction);
		}
		return (e_one->xwhole < e_two->xwhole);
	};
}

namespace sldraw {

	Polygon::~Polygon(void)
	{
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
		float I[3][4] = {{1.0,0.0,0.0,1.0}, {0.0,1.0,0.0,1.0}, {0.0,0.0,1.0,1.0}};
		float cR, cG, cB, cA;
		float uR, uG, uB, uA; // update RGBA value
		const int numEdges = lineList.size();
		std::map<int,Edge::Edge *> set; // Sorted Edge Table
		std::list<Edge::Edge *> aet; // Active Edge Table
		Edge::Edge *edge; // current edge

		// Initialize Colors
		cR = 1; cG = 1; cB = 1; cA = 1;
		uR = 0; uG = 0; uB = 0; uA = 0;

		// Data for aet
		int ylowest=10000;
		int ygreatest=0;

		int count = 0;
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
				uR = (I[(count+1)%3][0] - I[count][0])/dy;
				uG = (I[(count+1)%3][1] - I[count][1])/dy;
				uB = (I[(count+1)%3][2] - I[count][2])/dy;
				uA = (I[(count+1)%3][3] - I[count][3])/dy;
				cR = I[count][0];
				cG = I[count][1];
				cB = I[count][2];
				cA = I[count][3];
				count = (count+1)%3;
			} else if( randomFill && line->getys() > line->getye()) {
				uR = (I[count][0] - I[(count+1)%3][0])/dy;
				uG = (I[count][1] - I[(count+1)%3][1])/dy;
				uB = (I[count][2] - I[(count+1)%3][2])/dy;
				uA = (I[count][3] - I[(count+1)%3][3])/dy;
				cR = I[(count+1)%3][0];
				cG = I[(count+1)%3][1];
				cB = I[(count+1)%3][2];
				cA = I[(count+1)%3][3];
				count = (count+1)%3;
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

		Fl_Text_Buffer *textBuffer = NULL;
		if( printSET || printAET ) {
			textBuffer = textDisplay->buffer();
			textBuffer->append("Commencing Scanline...\n");
		}

		// std::cout << "Commencing Scanline..." << std::endl;

		while(!set.empty() || !aet.empty()) {

			if( printSET && !set.empty() ) {
				// std::cout << "Current SET/GET:" << std::endl;
				std::stringstream ostream;
				ostream << "Current SET/GET:" << std::endl;
				std::map<int,Edge::Edge*>::iterator mit = set.begin();
				for(; mit != set.end() ; ++mit) {
					Edge::Edge *tempEdge = (*mit).second;
					while(tempEdge != NULL) {
						// std::cout << "<" << tempEdge->ymax << "," << tempEdge->xwhole << "," << tempEdge->dx << "," << tempEdge->dy << ">" << std::endl;
						ostream << "<" << tempEdge->ymax << "," << tempEdge->xwhole << "," << tempEdge->dx << "," << tempEdge->dy << ">" << " @ y = " << y << std::endl;
						tempEdge = tempEdge->nextEdge;
					}
				}
				textBuffer->append(ostream.str().c_str());
			}
			
			// 1. ADD edges from set to aet
			if(set.count(y)>0) {
				if( printAET && !set.empty() ) {
					std::stringstream ostream;
					// std::cout << "Adding Edges to AET from SET/GET:" << std::endl;
					ostream << "Adding Edges to AET from SET/GET:" << std::endl;
					textBuffer->append(ostream.str().c_str());
				}
				Edge::Edge *tempEdge = set[y];
				while(tempEdge != NULL) {
					if( printAET && !set.empty() ) {
						std::stringstream ostream;
						// std::cout << "<" << tempEdge->ymax << "," << tempEdge->xwhole << "," << tempEdge->dx << "," << tempEdge->dy << ">" << y << std::endl;
						ostream << "<" << tempEdge->ymax << "," << tempEdge->xwhole << "," << tempEdge->dx << "," << tempEdge->dy << ">" << " @ y = " << y << std::endl;
						textBuffer->append(ostream.str().c_str());
					}
					aet.push_front(tempEdge);
					tempEdge = tempEdge->nextEdge;
				}
				set.erase(y);
			}

			if( printAET && !aet.empty() ) {
				std::stringstream ostream;
				// std::cout << "Current AET:" << std::endl;
				ostream << "Current AET:" << std::endl;
				std::list<Edge::Edge*>::iterator lit = aet.begin();
				for(; lit != aet.end() ; ++lit) {
					// std::cout << "<" << (*lit)->ymax << "," << (*lit)->xwhole << "," << (*lit)->dx << "," << (*lit)->dy << ">" << std::endl;
					ostream << "<" << (*lit)->ymax << "," << (*lit)->xwhole << "," << (*lit)->dx << "," << (*lit)->dy << ">" << " @ y = " << y << std::endl;
				}
				textBuffer->append(ostream.str().c_str());
			}

			// 2. REMOVE existing edges from aet
			std::list<Edge::Edge*> removeList;
			std::list<Edge::Edge*>::iterator it = aet.begin();
			for(; it != aet.end() ; ++it) {
				if((*it)->ymax <= y) {
					removeList.push_back(*it);
				}
			}
			it = removeList.begin();
			if( printAET && !aet.empty() ) {
				if(removeList.size() > 0) {
					std::stringstream ostream;
					// std::cout << "Removing Edges from AET:" << std::endl;
					ostream << "Removing Edges from AET:" << std::endl;
					textBuffer->append(ostream.str().c_str());
				}
			}
			for(; it != removeList.end() ; ++it) {
				if( printAET && !aet.empty() ) {
					std::stringstream ostream;
					// std::cout << "<" << (*it)->ymax << "," << (*it)->xwhole << "," << (*it)->dx << "," << (*it)->dy << ">" << std::endl;
					ostream << "<" << (*it)->ymax << "," << (*it)->xwhole << "," << (*it)->dx << "," << (*it)->dy << ">" << " @ y = " << y << std::endl;
					textBuffer->append(ostream.str().c_str());
				}
				aet.remove(*it);
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
			Edge::Edge* e1, * e2;
			// Skipping alpha for now
			// TODO: Add alpha back in for some reason?
			float r1, r2, g1, a1, g2, b1, b2, a2, ur, ug, ub, ua;
			it = aet.begin();
			for(; it != aet.end() ; ++it) {
				// Grab the first edge
				e1 = *it;
				r1 = e1->cR;
				g1 = e1->cG;
				b1 = e1->cB;
				a1 = e1->cA;
				// Then the second one
				it++;
				e2 = *it;
				r2 = e2->cR;
				g2 = e2->cG;
				b2 = e2->cB;
				a2 = e2->cA;
				// Calculate the update rate
				int diffx = e2->xwhole - e1->xwhole;
				ur = (r2-r1)/diffx;
				ug = (g2-g1)/diffx;
				ub = (b2-b1)/diffx;
				ua = (a2-a1)/diffx;
				for( int x = e1->xwhole ; x <= e2->xwhole ; ++x ) {
					glColor3f(r1,g1,b1);
					glVertex2i(x,y);
					r1 += ur;
					g1 += ug;
					b1 += ub;
					a1 += ua;
				}
			}

			// 5. INCREMENT y and UPDATE x-coord
			y++;
			it = aet.begin();
			Edge::Edge *temp;
			for(; it != aet.end() ; ++it) {
				temp= *it;
				temp->xfraction += abs(temp->dx);
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
				temp->cR += temp->uR;
				temp->cG += temp->uG;
				temp->cB += temp->uB;
				temp->cA += temp->uA;
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