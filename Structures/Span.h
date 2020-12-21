#ifndef SPAN_H
#define SPAN_H
#include "Point.h"

struct Span
{
	Span(Point p, int l, bool v);

	//Get the Point with the index 'i' in the string contained in the span
	Point GetPointInSpan(int i) const;
	friend std::ostream& operator << (std::ostream& os, const Span& span);

	Point point;
	int len;
	bool is_vert;
};
typedef std::vector<Span> Spans;
#endif