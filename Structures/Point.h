#ifndef POINT_H
#define POINT_H
#include "StringSet.h"

struct Point
{
	Point();
	Point(int r, int c);
	friend std::ostream& operator << (std::ostream& os, const Point& point);
	int row = 0;
	int col = 0;
};
#endif;
