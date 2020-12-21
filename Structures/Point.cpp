#include "Point.h"

Point::Point() {}
Point::Point(int r, int c) : row(r), col(c) {}
std::ostream& operator << (std::ostream& os, const Point& point)
{
	os << "(" << point.row << "," << point.col << ")";
	return os;
}