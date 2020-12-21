#include "Grid.h"

Grid::Grid() {}
int Grid::rows() const
{
	if (lines.empty())
	{
		return 0;
	}
	return lines.size();
}
int Grid::cols() const
{
	if (lines.empty())
	{
		return 0;
	}
	return lines[0].size();
}
bool Grid::in_bounds(const Point& p) const
{
	return (p.row >= 0 && p.row < rows() && p.col >= 0 && p.col < cols());
}
std::string Grid::GetSpanString(const Span& span, Attr& attr) const
{
	const int len = span.len;
	std::string temp;
	temp.resize(len);
	for (int i = 0; i < len; i++)
	{
		Point p = span.GetPointInSpan(i);
		char c = box(p);
		if (c == '-')
		{
			attr.has_blanks = true;
		}
		else if ((box(p) >= 'À' && box(p) <= 'ß') || box(p) == '¨')
		{
			attr.has_letters = true;
		}
		temp[i] = c;
	}
	return temp;
}
void Grid::WriteStringToSpan(const Span& span, const std::string& str)
{
	const int len = span.len;
	try
	{
		if (str.length() != len)
		{
			throw Exception("WriteStringToSpan: Different lengths for string and span");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	for (int i = 0; i < len; i++)
	{
		Point p = span.GetPointInSpan(i);
		write_box(p, str[i]);
	}
}
char Grid::box(const Point& p) const
{
	try
	{
		if (!in_bounds(p))
		{
			throw Exception("box: Point out of bounds");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	return lines[p.row][p.col];
}
void Grid::write_box(const Point& p, char c)
{
	try
	{
		if (!in_bounds(p))
		{
			throw Exception("write_box: Point out of bounds");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	lines[p.row][p.col] = c;
}
bool Grid::is_sign(const char sign, const Point& p) const
{
	return box(p) == sign;
}
bool Grid::is_letter(const Point& p) const
{
	return ((box(p) >= 'À' && box(p) <= 'ß') || box(p) == '¨');
}
bool Grid::Next(Point& p, bool is_vert, bool stop_at_wrap)
{
	if (is_vert)
	{
		p.row++;
		if (p.row >= rows())
		{
			p.row = 0;
			p.col++;
			if (stop_at_wrap)
			{
				return false;
			}
		}
	}
	else
	{
		p.col++;
		if (p.col >= cols())
		{
			p.col = 0;
			p.row++;
			if (stop_at_wrap)
			{
				return false;
			}
		}
	}
	return in_bounds(p);
}
void Grid::FillSpans(bool is_vert)
{
	Point p;
	while (in_bounds(p))
	{
		while (in_bounds(p) && is_sign('.', p))
		{
			Next(p, is_vert, false);
		}
		if (!in_bounds(p)) return;
		Point start_p = p;
		//cout << "Span start: " << p << endl;
		int len = 0;
		bool keep_going = false;
		do
		{
			keep_going = Next(p, is_vert, true);
			len++;
		} while (keep_going && !is_sign('.', p));
		//cout << "End of span. len = " << len << endl;
		if (len > 1)
		{
			if (max_span_size < len)
			{
				max_span_size = len;
			}
			spans.push_back(Span(start_p, len, is_vert));
		}
	}
}
void Grid::FillSpans()
{
	try
	{
		if (!spans.empty())
		{
			throw Exception("FillSpans: Spans is not empty");
		}
	}
	catch (Exception& exception)
	{
		std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
		Terminate();
	}
	FillSpans(false);
	FillSpans(true);
}
void Grid::LoadFromFile(std::string filename)
{
	std::ifstream f;
	f.open(filename);
	while (f.is_open() && !f.eof())
	{
		std::string line;
		getline(f, line);
		if (!line.empty() && line[0] != '#')
		{
			lines.push_back(line);
		}
	}
}
void Grid::ClearGrid()
{
	max_span_size = 0;
	lines.clear();
	spans.clear();
}
void Grid::Check() const
{
	for (int i = 0; i < rows(); i++)
	{
		try
		{
			if ((int)lines[i].size() != cols())
			{
				throw Exception("Grid::Check: Invalid grid");
			}
		}
		catch (Exception& exception)
		{
			std::cerr << "An exception occurred (" << exception.GetError() << ")" << std::endl;
			Terminate();
		}
	}
}
void Grid::PrintGrid() const
{
	for (std::string str : lines)
	{
		std::cout << "     ";
		for (int i = 0; i < str.size(); i++)
		{
			std::cout << str[i] << ' ';
		}
		std::cout << std::endl;
	}
}
void Grid::PrintSpans() const
{
	std::cout << "Spans:" << std::endl;
	for (const Span& span : spans)
	{
		Attr attr;
		std::cout << " " << span << " " << GetSpanString(span, attr) << std::endl;
	}
}