#include "Span.h"

Span::Span(Point p, int l, bool v) : point(p), len(l), is_vert(v) {}
Point Span::GetPointInSpan(int i) const
{
	try
	{
		if (i < 0 || i >= len)
		{
			throw Exception("GetPointInSpan: Index out of range");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}

	if (is_vert)
	{
		return Point(point.row + i, point.col);
	}
	else
	{
		return Point(point.row, point.col + i);
	}
}
std::ostream& operator << (std::ostream& os, const Span& span)
{
	os << span.point << " len = " << span.len << " is_vert = " << span.is_vert;
	return os;
}