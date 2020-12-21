#ifndef GRID_H
#define GRID_H
#include "Attr.h"

struct Grid
{
	Grid();
	int rows() const;
	int cols() const;

	//Returns true if 'p' within the grid
	bool in_bounds(const Point& p) const;

	//Returns the string contained in span
	std::string GetSpanString(const Span& span, Attr& attr) const;
	void WriteStringToSpan(const Span& span, const std::string& str);

	//Returns character value of the box at point 'p'
	//'p' must be in bounds
	char box(const Point& p) const;

	//Insert single character into the box inside the grid
	void write_box(const Point& p, char c);

	//Returns true if point value is a specific sign in the grid
	bool is_sign(const char sign, const Point& p) const;

	//Returns true if point value is an any letter
	bool is_letter(const Point& p) const;

	//Increments the point across the grid, one box at a time
	//If stop_at_wrap == false retuns true if point is still in bounds
	//If stop_at_wrap == true retuns false at every wrap
	bool Next(Point& p, bool is_vert, bool stop_at_wrap);

	//Add to 'spans' vector with vert/horiz spans in the grid
	void FillSpans(bool is_vert);

	//Add to 'spans' vector with all viable spans in the grid
	void FillSpans();
	void LoadFromFile(std::string filename);
	void ClearGrid();
	void Check() const;
	void PrintGrid() const;
	void PrintSpans() const;

	int max_span_size = 0;
	std::vector<std::string> lines;
	Spans spans;
};
#endif
