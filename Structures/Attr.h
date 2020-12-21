#ifndef ATTR_H
#define ATTR_H

#include "../Classes/Library.h"

//Span attributes
struct Attr
{
	bool is_empty() const;
	bool is_partial() const;
	bool is_full() const;

	bool has_letters = false;
	bool has_blanks = false;
};

#endif
